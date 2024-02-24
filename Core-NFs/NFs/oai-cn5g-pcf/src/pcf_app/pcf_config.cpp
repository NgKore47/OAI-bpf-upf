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

/*! \file pcf_config_types.cpp
 \brief
 \author  Stefan Spettel
 \company phine.tech
 \date 2023
 \email: stefan.spettel@phine.tech
*/

#include "pcf_config.hpp"

oai::config::pcf::pcf_config::pcf_config(
    const std::string& config_path, bool log_stdout, bool log_rot_file)
    : config(
          config_path, oai::config::PCF_CONFIG_NAME, log_stdout, log_rot_file) {
  m_used_sbi_values = {
      oai::config::PCF_CONFIG_NAME, oai::config::NRF_CONFIG_NAME};
  m_used_config_values = {
      oai::config::LOG_LEVEL_CONFIG_NAME, oai::config::REGISTER_NF_CONFIG_NAME,
      oai::config::NF_LIST_CONFIG_NAME, oai::config::PCF_CONFIG_NAME,
      oai::config::NF_CONFIG_HTTP_NAME};

  auto pcf = std::make_shared<pcf_config_type>(
      PCF_CONFIG_NAME, "oai-pcf",
      sbi_interface("SBI", "oai-pcf", 80, "v1", "eth0"),
      policy_config(
          DEFAULT_POLICY_DECISIONS_PATH, DEFAULT_PCC_RULES_PATH,
          DEFAULT_TRAFFIC_RULES_PATH, DEFAULT_QOS_DATA_PATH));

  auto nrf = std::make_shared<nf>(
      NRF_CONFIG_NAME, "oai-nrf",
      sbi_interface("SBI", "oai-nrf", 80, "v1", ""));

  add_nf(PCF_CONFIG_NAME, pcf);
  add_nf(NRF_CONFIG_NAME, nrf);
}

const oai::config::pcf::policy_config&
oai::config::pcf::pcf_config::get_pcf_policy() const {
  return std::dynamic_pointer_cast<pcf_config_type>(get_local())
      ->get_policy_config();
}
