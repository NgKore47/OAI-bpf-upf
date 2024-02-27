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

/*! \file individual_sm_policy_document_api_handler.cpp
 \brief
 \author  Stefan Spettel
 \company phine.tech
 \date 2023
 \email: stefan.spettel@phine.tech
 */

#include "individual_sm_policy_document_api_handler.h"
#include "ProblemDetails.h"

namespace oai::pcf::api {

using namespace oai::model::pcf;
using namespace oai::model::common;
using namespace oai::pcf::app::sm_policy;

api_response individual_sm_policy_document_api_handler::delete_sm_policy(
    const std::string& sm_policy_id,
    const SmPolicyDeleteData& sm_policy_delete_data) {
  api_response response;

  ProblemDetails problem_details;
  std::string problem_description;
  std::string content_type = "application/problem+json";
  nlohmann::json json_data;
  http_status_code_e http_code;
  status_code res = m_smpc_service->delete_sm_policy_handler(
      sm_policy_id, sm_policy_delete_data, problem_description);

  switch (res) {
    case status_code::OK:
      http_code = http_status_code_e::HTTP_STATUS_CODE_204_NO_CONTENT;
      break;

    case status_code::NOT_FOUND:
      problem_details.setDetail(problem_description);
      // This is not defined in the standard
      problem_details.setCause("SM_POLICY_ID_NOT_FOUND");
      http_code = http_status_code_e::HTTP_STATUS_CODE_404_NOT_FOUND;
      break;

    default:
      problem_details.setDetail("Internal Service Error: Unknown return code.");
      problem_details.setCause("INTERNAL_ERROR");
      http_code =
          http_status_code_e::HTTP_STATUS_CODE_500_INTERNAL_SERVER_ERROR;
  }
  response.status_code = http_code;
  if (res != status_code::OK) {
    response.headers.add<Pistache::Http::Header::ContentType>(
        Pistache::Http::Mime::MediaType(content_type));
    to_json(json_data, problem_details);
    response.body = json_data.dump();
  }
  return response;
}

api_response individual_sm_policy_document_api_handler::get_sm_policy(
    const std::string& sm_policy_id) {
  api_response response;
  ProblemDetails problem_details;
  std::string problem_description;
  std::string content_type = "application/problem+json";
  nlohmann::json json_data;
  http_status_code_e http_code;

  SmPolicyControl sm_policy_control;

  status_code res = m_smpc_service->get_sm_policy_handler(
      sm_policy_id, sm_policy_control, problem_description);

  switch (res) {
    case status_code::OK:
      http_code    = http_status_code_e::HTTP_STATUS_CODE_200_OK;
      content_type = "application/json";
      break;

    case status_code::NOT_FOUND:
      problem_details.setDetail(problem_description);
      // This is not defined in the standard
      problem_details.setCause("SM_POLICY_ID_NOT_FOUND");
      http_code = http_status_code_e::HTTP_STATUS_CODE_404_NOT_FOUND;
      break;

    default:
      problem_details.setDetail("Internal Service Error: Unknown return code.");
      problem_details.setCause("INTERNAL_ERROR");
      http_code =
          http_status_code_e::HTTP_STATUS_CODE_500_INTERNAL_SERVER_ERROR;
  }

  if (res == status_code::OK) {
    to_json(json_data, sm_policy_control);
  } else {
    to_json(json_data, problem_details);
  }
  response.status_code = http_code;
  response.body        = json_data.dump();
  response.headers.add<Pistache::Http::Header::ContentType>(
      Pistache::Http::Mime::MediaType(content_type));

  return response;
}

api_response individual_sm_policy_document_api_handler::update_sm_policy(
    const std::string& sm_policy_id,
    const SmPolicyUpdateContextData& sm_policy_update_context_data) {
  api_response response;
  ProblemDetails problem_details;
  std::string problem_description;
  std::string content_type = "application/problem+json";
  nlohmann::json json_data;
  http_status_code_e http_code;

  SmPolicyDecision decision_update;

  status_code res = m_smpc_service->update_sm_policy_handler(
      sm_policy_id, sm_policy_update_context_data, decision_update,
      problem_description);

  problem_details.setDetail(problem_description);

  switch (res) {
    case status_code::OK:
      content_type = "application/json";
      http_code    = http_status_code_e::HTTP_STATUS_CODE_200_OK;
      break;
    case status_code::INVALID_PARAMETERS:
      http_code = http_status_code_e::HTTP_STATUS_CODE_400_BAD_REQUEST;
      problem_details.setCause("ERROR_INITIAL_PARAMETERS");
      break;
    case status_code::CONTEXT_DENIED:
      // should map to 403 but not defined in standard for this request
      http_code = http_status_code_e::HTTP_STATUS_CODE_400_BAD_REQUEST;
      problem_details.setCause("ERROR_INITIAL_PARAMETERS");
      break;
    case status_code::NOT_FOUND:
      // TODO This is not defined in the standard, but this scenario is missing
      // we could map it to the 400 Bad request but that is somehow misleading
      problem_details.setCause("SM_POLICY_ID_NOT_FOUND");
      http_code = http_status_code_e::HTTP_STATUS_CODE_404_NOT_FOUND;
      break;
    default:
      problem_details.setCause("INTERNAL_ERROR");
      http_code =
          http_status_code_e::HTTP_STATUS_CODE_500_INTERNAL_SERVER_ERROR;
  }

  if (res == status_code::OK) {
    to_json(json_data, decision_update);
  } else {
    to_json(json_data, problem_details);
  }

  response.headers.add<Pistache::Http::Header::ContentType>(
      Pistache::Http::Mime::MediaType(content_type));
  response.body        = json_data.dump();
  response.status_code = http_code;
  return response;
}
}  // namespace oai::pcf::api
