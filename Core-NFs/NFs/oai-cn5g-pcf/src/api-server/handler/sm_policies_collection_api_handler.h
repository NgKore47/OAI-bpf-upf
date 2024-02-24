
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

/*! \file sm_policies_collection_api_handler.h
 \brief
 \author  Stefan Spettel
 \company phine.tech
 \date 2023
 \email: stefan.spettel@phine.tech
 */

#pragma once

#include "3gpp_29.500.h"
#include "api_response.h"
#include "SmPolicyContextData.h"
#include "pcf_sm_policy_control.hpp"

namespace oai::pcf::api {

class sm_policies_collection_api_handler {
 public:
  sm_policies_collection_api_handler(
      const std::shared_ptr<oai::pcf::app::pcf_smpc>& pcf_smpc,
      const std::string& address) {
    m_address      = address;
    m_smpc_service = pcf_smpc;
  }

  /**
   * Create SM Policy
   * @param sm_policy_context_data SM context data
   * @return api_response with SmPolicyDecision
   */
  api_response create_sm_policy(
      const oai::model::pcf::SmPolicyContextData& sm_policy_context_data);

 private:
  std::string m_address;
  std::shared_ptr<oai::pcf::app::pcf_smpc> m_smpc_service;
};

}  // namespace oai::pcf::api