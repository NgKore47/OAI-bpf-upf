/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file pcf_http2-server.h
 \brief
 \author  Rohan Kharade, Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2023
 \email: rohan.kharade@openairinterface.org
 */

#include "pcf-http2-server.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>

#include "3gpp_29.500.h"
#include "logger.hpp"
#include "pcf_config.hpp"
#include "api_defs.h"
#include "SmPolicyContextData.h"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
using namespace oai::model::pcf;
using namespace oai::config::pcf;
using namespace oai::pcf::api;

extern std::unique_ptr<pcf_config> pcf_cfg;

//------------------------------------------------------------------------------
void pcf_http2_server::start() {
  boost::system::error_code ec;

  Logger::pcf_sbi().info("HTTP2 server started");
  std::string nfId           = {};
  std::string subscriptionID = {};

  // SM Policies Collection API
  server.handle(
      sm_policies::get_route(),
      [&](const request& request, const response& response) {
        if (request.method() != "POST") {
          handle_method_not_exists(response, request);
          return;
        }
        auto request_body = std::make_shared<std::stringstream>();

        request.on_data(
            [&, request_body](const uint8_t* data, std::size_t len) {
              if (len > 0) {
                std::copy(
                    data, data + len,
                    std::ostream_iterator<uint8_t>(*request_body));
                return;
              }
              SmPolicyContextData context;
              try {
                nlohmann::json::parse(request_body->str()).get_to(context);
                context.validate();
                api_response resp =
                    m_collection_api_handler->create_sm_policy(context);
                auto h_map = convert_headers(resp);
                response.write_head(
                    static_cast<unsigned int>(resp.status_code), h_map);
                response.end(resp.body);
                return;
              } catch (std::exception& e) {
                handle_parsing_error(response, e);
                return;
              }
            });
      });

  // Individual SM Policy
  // We match for sm-policies/*
  server.handle(
      sm_policies::get_route() + "/",
      [&](const request& request, const response& response) {
        std::vector<std::string> split_result;
        boost::split(split_result, request.uri().path, boost::is_any_of("/"));
        bool is_update = false;
        bool is_delete = false;
        bool is_get    = false;
        std::string policy_id;
        if (split_result[split_result.size() - 1] == "delete") {
          is_delete = true;
          policy_id = split_result[split_result.size() - 2];
        } else if (split_result[split_result.size() - 1] == "update") {
          is_update = true;
          policy_id = split_result[split_result.size() - 2];
        } else {
          is_get    = true;
          policy_id = split_result[split_result.size() - 1];
        }
        if ((is_delete || is_update) && request.method() != "POST") {
          handle_method_not_exists(response, request);
          return;
        }
        if (is_get && request.method() != "GET") {
          handle_method_not_exists(response, request);
          return;
        }
        auto request_body = std::make_shared<std::stringstream>();

        request.on_data([&, request_body, is_get, is_update, is_delete,
                         policy_id](const uint8_t* data, std::size_t len) {
          if (len > 0) {
            std::copy(
                data, data + len,
                std::ostream_iterator<uint8_t>(*request_body));
            return;
          }
          SmPolicyDeleteData delete_data;
          SmPolicyUpdateContextData update_context_data;
          api_response resp;
          try {
            if (is_update) {
              nlohmann::json::parse(request_body->str())
                  .get_to(update_context_data);
              update_context_data.validate();
              resp = m_individual_api_handler->update_sm_policy(
                  policy_id, update_context_data);
            } else if (is_delete) {
              nlohmann::json::parse(request_body->str()).get_to(delete_data);
              delete_data.validate();
              resp = m_individual_api_handler->delete_sm_policy(
                  policy_id, delete_data);
            } else if (is_get) {
              resp = m_individual_api_handler->get_sm_policy(policy_id);
            }
            auto h_map = convert_headers(resp);
            response.write_head(
                static_cast<unsigned int>(resp.status_code), h_map);
            response.end(resp.body);
            return;
          } catch (std::exception& e) {
            handle_parsing_error(response, e);
            return;
          }
        });
      });

  // Default Route
  server.handle("/", [&](const request& request, const response& response) {
    handle_method_not_exists(response, request);
    return;
  });

  if (server.listen_and_serve(ec, m_address, std::to_string(m_port))) {
    Logger::pcf_sbi().error("HTTP Server error: %s", ec.message());
  }
}

void pcf_http2_server::stop() {
  server.stop();
}

void pcf_http2_server::handle_method_not_exists(
    const response& response, const request& request) {
  Logger::pcf_sbi().warn(
      "Invalid route/method called: %s : %s", request.method(),
      request.uri().path);
  response.write_head(static_cast<unsigned int>(
      http_status_code_e::HTTP_STATUS_CODE_404_NOT_FOUND));
  response.end("The requested method does not exist");
}

void pcf_http2_server::handle_parsing_error(
    const response& response, const std::exception& ex) {
  Logger::pcf_sbi().warn("Parsing error: %s", ex.what());
  response.write_head(static_cast<unsigned int>(
      http_status_code_e::HTTP_STATUS_CODE_400_BAD_REQUEST));
  // for security reasons it is better to not give the internal exception to the
  // user, we can also decide to change that
  response.end("Could not parse JSON data");
}

header_map pcf_http2_server::convert_headers(const api_response& response) {
  header_map h_map;
  for (const auto& hdr : response.headers.list()) {
    std::stringstream ss;
    hdr->write(ss);
    h_map.emplace(hdr->name(), header_value{ss.str(), false});
  }
  return h_map;
}
