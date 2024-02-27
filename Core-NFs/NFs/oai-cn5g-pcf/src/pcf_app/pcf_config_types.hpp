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

#pragma once
#include "config_types.hpp"

namespace oai::config::pcf {

class policy_config : public config_type {
 private:
  string_config_value m_pcc_rules_path;
  string_config_value m_policy_decisions_path;
  string_config_value m_traffic_rules_path;
  string_config_value m_qos_data_path;

 public:
  explicit policy_config(
      const std::string& policy_decisions_path,
      const std::string& pcc_rules_path, const std::string& traffic_rules_path,
      const std::string& qos_data_path);

  void from_yaml(const YAML::Node& node) override;

  [[nodiscard]] std::string to_string(const std::string& indent) const override;
  [[nodiscard]] const std::string& get_pcc_rules_path() const;
  [[nodiscard]] const std::string& get_policy_decisions_path() const;
  [[nodiscard]] const std::string& get_traffic_rules_path() const;
  [[nodiscard]] const std::string& get_qos_data_path() const;
};

class pcf_config_type : public nf {
 private:
  policy_config m_policy_config;

 public:
  explicit pcf_config_type(
      const std::string& name, const std::string& host,
      const sbi_interface& sbi, const policy_config& policy);

  void from_yaml(const YAML::Node& node) override;

  [[nodiscard]] std::string to_string(const std::string& indent) const override;

  void validate() override;

  [[nodiscard]] const policy_config& get_policy_config() const;
};

}  // namespace oai::config::pcf