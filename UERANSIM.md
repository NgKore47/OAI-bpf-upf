### Changes in configuration files of GnB

- `Core-NFs/UERANSIM-OAI/config/custom-gnb.yaml`
```diff
@@ -1,23 +1,23 @@
-mcc: '286'          # Mobile Country Code value
-mnc: '01'           # Mobile Network Code value (2 or 3 digits)
+mcc: '208'          # Mobile Country Code value
+mnc: '95'           # Mobile Network Code value (2 or 3 digits)
 
 nci: '0x000000010'  # NR Cell Identity (36-bit)
 idLength: 32        # NR gNB ID length in bits [22...32]
-tac: 1              # Tracking Area Code
+tac: 0xa000           # Tracking Area Code
 
-linkIp: 127.0.0.1   # gNB's local IP address for Radio Link Simulation (Usually same with local IP)
-ngapIp: 127.0.0.1   # gNB's local IP address for N2 Interface (Usually same with local IP)
-gtpIp: 127.0.0.1    # gNB's local IP address for N3 Interface (Usually same with local IP)
+linkIp: 192.168.5.241   # gNB's local IP address for Radio Link Simulation (Usually same with local IP)
+ngapIp: 192.168.5.241   # gNB's local IP address for N2 Interface (Usually same with local IP)
+gtpIp: 192.168.5.217    # gNB's local IP address for N3 Interface (Usually same with local IP)
 
 # List of AMF address information
 amfConfigs:
-  - address: 127.0.0.5
+  - address: 192.168.5.241
     port: 38412
 
 # List of supported S-NSSAIs by this gNB
 slices:
-  - sst: 1
-    sd: 1
+  - sst: 222
+    sd: 123
 
 # Indicates whether o
```

### Changes in configuration files of UE 

- `Core-NFs/UERANSIM-OAI/config/custom-ue.yaml`
```diff
# IMSI number of the UE. IMSI = [MCC|MNC|MSISDN] (In total 15 digits)
-supi: 'imsi-286010000000001'
+supi: 'imsi-208950000000031'
 # Mobile Country Code value of HPLMN
-mcc: '286'
+mcc: '208'
 # Mobile Network Code value of HPLMN (2 or 3 digits)
-mnc: '93'
+mnc: '95'
 
 # Permanent subscription key
-key: '465B5CE8B199B49FAA5F0A2EE238A6BC'
+key: '0C0A34601D4F07677303652C0462535B'
 # Operator code (OP or OPC) of the UE
-op: 'E8ED289DEBA952E4283B54E88E6183CA'
+op: '63bfa50ee6523365ff14c1f45f88737d'
 # This value specifies the OP type and it can be either 'OP' or 'OPC'
-opType: 'OP'
+opType: 'OPC'
 # Authentication Management Field (AMF) value
 amf: '8000'
 # IMEI number of the device. It is used if no SUPI is provided
 imei: '356938035643803'
 # IMEISV number of the device. It is used if no SUPI and IMEI is provided
-imeiSv: '4370816125816151'
+imeiSv: '0035609204079514'
 
 # List of gNB IP addresses for Radio Link Simulation
 gnbSearchList:
-  - 127.0.0.1
+  - 192.168.5.241
 
 ...
 # Initial PDU sessions to be established
 sessions:
   - type: 'IPv4'
-    apn: 'internet'
+    apn: 'default'
     slice:
-      sst: 1
-      sd: 1
+      sst: 222
+      sd: 123
 
 # Configured NSSAI for this UE by HPLMN
 configured-nssai:
-  - sst: 1
-    sd: 1
+  - sst: 222
+    sd: 123
 
 # Default Configured NSSAI for this UE
 default-nssai:
-  - sst: 1
-    sd: 1
+  - sst: 222
+    sd: 123

```


### Changes we made in UERANSIM source code 

```diff
--- a/src/ue/nas/mm/messaging.cpp
+++ b/src/ue/nas/mm/messaging.cpp
@@ -210,11 +210,11 @@ void NasMm::receiveNasMessage(const nas::NasMessage &msg)
             m_logger->err(
                 "Not integrity protected NAS message received after security establishment. Ignoring received "
                 "NAS message");
-            return;
+            // return;
         }
 
         receiveMmMessage((const nas::PlainMmMessage &)mmMsg);
-        return;
+        // return;
     }
 
     auto &securedMm = (const nas::SecuredMmMessage &)mmMsg;
diff --git a/src/ue/nas/mm/security.cpp b/src/ue/nas/mm/security.cpp
index 8d54167..8be9290 100644
--- a/src/ue/nas/mm/security.cpp
+++ b/src/ue/nas/mm/security.cpp
@@ -87,9 +87,9 @@ void NasMm::receiveSecurityModeCommand(const nas::SecurityModeCommand &msg)
         }
         else
         {
-            m_logger->err("[IA0, EA0] cannot be accepted as the UE does not have an emergency");
-            reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
-            return;
+            // m_logger->err("[IA0, EA0] cannot be accepted as the UE does not have an emergency");
+            // reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
+            // return;
         }
     }
 
@@ -128,9 +128,9 @@ void NasMm::receiveSecurityModeCommand(const nas::SecurityModeCommand &msg)
 
         if (integrity == nas::ETypeOfIntegrityProtectionAlgorithm::IA0 && !(hasEmergency() || locallyDerived))
         {
-            m_logger->err("[IA0] cannot be accepted as the UE does not have an emergency");
-            reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
-            return;
+            // m_logger->err("[IA0] cannot be accepted as the UE does not have an emergency");
+            // reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
+            // return;
         }
     }
 
@@ -173,8 +173,8 @@ void NasMm::receiveSecurityModeCommand(const nas::SecurityModeCommand &msg)
             {
                 // If it still mismatched, reject the security mode command
                 m_logger->err("Security Mode Command integrity check failed");
-                reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
-                return;
+                // reject(nas::EMmCause::SEC_MODE_REJECTED_UNSPECIFIED);
+                // return;
             }
             else
             {

```
