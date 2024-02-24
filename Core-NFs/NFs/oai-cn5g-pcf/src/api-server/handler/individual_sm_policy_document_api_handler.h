
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

#pragma once

#include "3gpp_29.500.h"
#include "api_response.h"
#include "pcf_sm_policy_control.hpp"
#include "SmPolicyDeleteData.h"
#include "SmPolicyUpdateContextData.h"

namespace oai::pcf::api {

class individual_sm_policy_document_api_handler {
 public:
  explicit individual_sm_policy_document_api_handler(
      const std::shared_ptr<oai::pcf::app::pcf_smpc>& pcf_smpc) {
    m_smpc_service = pcf_smpc;
  }
  /**
   * Delete SM Policy based on ID
   * @param sm_policy_id
   * @param sm_policy_delete_data
   * @return api_response
   */
  api_response delete_sm_policy(
      const std::string& sm_policy_id,
      const oai::model::pcf::SmPolicyDeleteData& sm_policy_delete_data);

  /**
   * Get SM Policy by ID
   * @param sm_policy_id
   * @return api_response
   */
  api_response get_sm_policy(const std::string& sm_policy_id);

  /**
   * Update SM Policy by ID and mandatory update context data
   * @param sm_policy_id
   * @param smPolicyUpdateContextData
   * @return
   */
  api_response update_sm_policy(
      const std::string& sm_policy_id,
      const oai::model::pcf::SmPolicyUpdateContextData&
          smPolicyUpdateContextData);

 private:
  std::shared_ptr<oai::pcf::app::pcf_smpc> m_smpc_service;
};

}  // namespace oai::pcf::api