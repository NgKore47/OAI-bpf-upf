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

/*! \file nssf_config_types.cpp
 \brief
 \author  Stefan Spettel
 \company phine.tech
 \date 2023
 \email: stefan.spettel@phine.tech
*/

#include "nssf_config_types.hpp"

#include "config.hpp"

using namespace oai::config;
using namespace oai::config::nssf;

nssf_config_type::nssf_config_type(
    const std::string& name, const std::string& host, const sbi_interface& sbi,
    const std::string& slice_config_path)
    : nf(name, host, sbi) {
  m_slice_config_path =
      string_config_value("Slice Config Path", slice_config_path);
}

void nssf_config_type::from_yaml(const YAML::Node& node) {
  nf::from_yaml(node);
  if (node["slice_config_path"]) {
    m_slice_config_path.from_yaml(node["slice_config_path"]);
  }
}

std::string nssf_config_type::to_string(const std::string& indent) const {
  std::string out      = nf::to_string("");
  unsigned inner_width = get_inner_width(indent.length());
  out.append(indent).append(fmt::format(
      BASE_FORMATTER, OUTER_LIST_ELEM, m_slice_config_path.get_config_name(),
      inner_width, m_slice_config_path.to_string(indent)));
  return out;
}

void nssf_config_type::validate() {
  nf::validate();
  m_slice_config_path.validate();
}

const std::string& nssf_config_type::get_slice_config_path() const {
  return m_slice_config_path.get_value();
}
