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
 \date 2022
 \email: rohan.kharade@openairinterface.org
 */

#pragma once

#include "conversions.hpp"
#include "pcf.h"
#include "pcf_app.hpp"
#include "string.hpp"
#include "uint_generator.hpp"
#include <nghttp2/asio_http2_server.h>
#include "IndividualSMPolicyDocumentApiImpl.h"
#include "SMPoliciesCollectionApiImpl.h"
#include "sm_policies_collection_api_handler.h"
#include "individual_sm_policy_document_api_handler.h"

namespace oai::pcf::api {

class pcf_http2_server {
 public:
  pcf_http2_server(
      const std::string& addr, uint32_t port,
      const std::unique_ptr<oai::pcf::app::pcf_app>& pcf_app_inst)
      : m_address(addr), m_port(port), server() {
    // TODO hardcode http string, how to handle https
    std::string address = "http://" + addr + ":" + std::to_string(port);

    m_collection_api_handler =
        std::make_shared<sm_policies_collection_api_handler>(
            pcf_app_inst->get_pcf_smpc_service(), address);

    m_individual_api_handler =
        std::make_shared<individual_sm_policy_document_api_handler>(
            pcf_app_inst->get_pcf_smpc_service());
  };

  void start();
  void init(size_t /* thr */) {}

  // PCF

  void stop();

 private:
  util::uint_generator<uint32_t> m_promise_id_generator;
  std::string m_address;
  uint32_t m_port;

  nghttp2::asio_http2::server::http2 server;

  std::shared_ptr<sm_policies_collection_api_handler> m_collection_api_handler;
  std::shared_ptr<individual_sm_policy_document_api_handler>
      m_individual_api_handler;

  static void handle_method_not_exists(
      const nghttp2::asio_http2::server::response& response,
      const nghttp2::asio_http2::server::request& request);

  static void handle_parsing_error(
      const nghttp2::asio_http2::server::response& response,
      const std::exception& ex);

  static nghttp2::asio_http2::header_map convert_headers(
      const api_response& response);
};

}  // namespace oai::pcf::api
