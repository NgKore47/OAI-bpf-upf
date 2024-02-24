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

/*! \file pcf_config.hpp
 \brief
 \author  Rohan Kharade, Stefan Spettel
 \company OpenAirInterface Software Alliance
 \date 2022
 \email: rohan.kharade@openairinterface.org
*/

#pragma once

#include "config.hpp"
#include "pcf_config_types.hpp"

namespace oai::config::pcf {

const std::string DEFAULT_PCC_RULES_PATH = "/openair-pcf/policies/pcc_rules";
const std::string DEFAULT_TRAFFIC_RULES_PATH =
    "/openair-pcf/policies/traffic_rules";
const std::string DEFAULT_POLICY_DECISIONS_PATH =
    "/openair-pcf/policies/policy_decisions";
const std::string DEFAULT_QOS_DATA_PATH = "/openair-pcf/policies/qos_data";

class pcf_config : public oai::config::config {
 public:
  explicit pcf_config(
      const std::string& config_path, bool log_stdout, bool log_rot_file);

  const policy_config& get_pcf_policy() const;
};
}  // namespace oai::config::pcf
