.. _softdevice_controller_changelog:

Changelog
#########

.. contents::
   :local:
   :depth: 2

All the notable changes to this project are documented on this page.

Main branch
***********

Added
=====

* Central-only and Peripheral-only library variants for the nRF54L Series devices. (DRGN-25081)
* Support for generating paEventCounter reports using the VS Enable Periodic Advertising Event Counter Reports command (DRGN-25444).
* The :c:func:`sdc_support_channel_sounding_initiator_role` and :c:func:`sdc_support_channel_sounding_reflector_role` functions, which can reduce the NVM usage of Channel Sounding by removing support for the Initiator or Reflector role (DRGN-23607).

Bug fixes
=========

* Fixed a rare issue where the controller would assert when scanning and initiating simultaneously. (DRGN-25478)

  The issue would only happen if all the following conditions are met:

    * The scan interval and scan window used by the initiator were not equal to those used by the scanner.
    * The Bluetooth host temporarily stopped pulling HCI events.
    * The initiator received a connectable ``ADV_EXT_IND``.

* Fixed an issue where mode-0 steps in a Channel Sounding subevent would compensate for a random frequency actuation error when using the LE CS Test HCI command (DRGN-25522).
* Fixed an issue where the controller would assert when terminating a connection created from PAwR.
  The issue would occur if the :kconfig:option:`CONFIG_BT_CTLR_CHANNEL_SOUNDING` Kconfig option was enabled. (DRGN-25200)
* Fixed a rare issue where the controller could assert when calling the ``LE Create Connection Cancel`` HCI command. (DRGN-25326)
* Fixed an issue where the controller could assert when receiving on the Coded PHY over an ACL connection.
  This would occur when coding indicator or length byte was corrupted, causing the controller to listen for more than 27 bytes on S8 Coded PHY. (DRGN-24930)
* Fixed a rare issue where the controller could stop responding when using coexistence interfaces with the SoftDevice Controller on nRF52 or nRF53 Series devices. (DRGN-25846)
* Fixed a rare issue where the controller acting as a central would cause the link to time out.
  This would occur when a connection subrate factor greater than ``1`` was used, and a conflicting scheduling activity was running. (DRGN-25801)

Changes
=======

* The ``Version`` field in the ``LL_VERSION_IND`` packet now contains the value ``0x0F`` to indicate compatibility with Bluetooth Core Specification v6.1 (DRGN-25531).
* When controller to host flow control is enabled, the controller no longer waits until all ACL data packets have been acknowledged by the host before raising the Disconnection Complete event.
  The controller no longer validates the handles provided in the Host Number of Complete Packets command.
  That is, the handles provided may belong to a Disconnection Complete event which has not yet been processed by the host.
  This reverts the changes done by DRGN-21085. (DRGN-24882)
* The packets received on Coded PHY with reserved for future use (RFU) values in the coding indicator (CI) field are now treated as CRC errors.
  This would occur when the CI field is corrupted in noisy environments, causing the controller to decode at an incorrect rate. (DRGN-25037)

nRF Connect SDK v3.0.0
**********************

Added
=====

* Support generating the HCI LE CIS Established v2 event. (DRGN-24112)
* Support for the Advertising Coding Selection feature as an advertiser or scanner. (DRGN-23744)

  * For an advertiser, this adds support for the LE Set Extended Advertising Parameters [v2] HCI command.
  * For a scanner, the advertising reports will contain the coding scheme for packets received over LE Coded PHY when the host feature bit is enabled.
* Support for multiple packet pairs in an ACL event when using LLPM mode. (DRGN-16157)

Changes
=======

* The Channel Sounding feature is now :ref:`supported <nrf:software_maturity>` instead of experimental. (DRGN-24060)
* The LE Channel Selection Algorithm event is no longer raised when a connection was established as a peripheral using legacy advertising commands.
  This behavior was changed to accommodate ES-27170. (DRGN-24660)
* The CIS or BIS sink now generate lost SDUs immediately when scheduling conflicts occur instead of after receiving the next valid SDU. (DRGN-24062)
* Removed support for running the SoftDevice Controller on the nRF54L15 DK v0.8.1 and earlier. (DRGN-21403)
* Reduced latency when changing the list of subevents to which a Periodic Advertising with Responses Scanner is synchronized. (DRGN-24543)
* A CIS peripheral will now reject an invalid ``LL_CIS_REQ`` if one of the following condition is met:

  * ``SDU_Interval_C_To_P`` or ``SDU_Interval_P_To_C`` is less than 255 µs.
  * ``ISO_Interval`` is not an integer multiple of ``SDU_Interval_C_To_P`` or ``SDU_Interval_P_To_C`` when unframed PDU is used.
  * ``BN_C_To_P`` or ``BN_P_To_C`` is smaller than the value required by the configuration when an unframed PDU is used.

  This only applies when the burst number (BN) in the corresponding direction (``BN_C_To_P`` or ``BN_P_To_C``) is non-zero. (DRGN-23304)

Bug fixes
=========

* Fixed an issue where disconnect could happen if multiple peripheral links were active and encrypted. (DRGN-24784)
* Fixed an issue where the controller would fail to synchronize with a BIS Broadcaster. (DRGN-24670)

  This would occur when the Broadcaster has set ``Num_Bis=1``, ``NSE > 1``, and ``Sub_Interval == BIS_Spacing``.
  Previously, the controller would raise the LE BIG Sync Established event with status set to ``Unsupported Feature or Parameter value (0x11)``.
* Fixed an issue where ACL connections could not be created if a Periodic Advertiser was configured when the :kconfig:option:`CONFIG_BT_CTLR_SDC_PAWR_ADV` Kconfig option was selected. (DRGN-24148)
* Fixed a rare issue where the scanner would assert when scanning and initiating at the same time. (DRGN-24198)

  The issue would only happen if all the following conditions are met:

    * :kconfig:option:`BT_CTLR_SDC_ALLOW_PARALLEL_SCANNING_AND_INITIATING` is selected.
    * :kconfig:option:`BT_CTLR_SDC_SCAN_BUFFER_COUNT` is set to the non-default value 2.
    * The initiator has received a connectable ``ADV_EXT_IND``.
    * The initiator is canceled.
* Fixed an issue where the central device would disconnect 40 s after responding to a ``LL_SUBRATE_REQ`` with reason ``LMP Response Timeout (0x22)``.
  This would only occur on nRF52 Series and nRF53 Series devices. (DRGN-24310)
* Fixed a very rare issue where the scanner would assert, hang or stop producing reports when scanning and initiating at the same time. (DRGN-24370)

  The issue would only happen if all the following conditions are met:

    * :kconfig:option:`BT_CTLR_SDC_ALLOW_PARALLEL_SCANNING_AND_INITIATING` is selected.
    * The timing events are not combined for the scanner and the initiator.
    * The initiator is canceled or the scanner is stopped after receiving an extended advertising PDU pointing to a AUX_ADV_IND or AUX_CHAIN_IND PDU, but the AUX_ADV_IND or AUX_CHAIN_IND PDU was not received yet.
      The issue may also occur if the reception of the AUX_ADV_IND or AUX_CHAIN_IND fails to be scheduled.

    See :ref:`concurrent_scanner_initiator_timing` for information on how to select parameters where the timing events are combined.
* Fixed a rare issue where the scanner would fail to receive a secondary channel packet. (DRGN-24300)

  The issue would only happen if all the conditions are met:

    * The configured scan window is larger than 500 milliseconds.
    * The ``ADV_EXT_IND`` is received at the very end of the scan window.
* Fixed an issue where the CIS peripheral would not be able to receive after the first subevent.
  This would only happen if the subevent interval is large or if the CIS is configured with interleaved packing. (DRGN-24359)
* Fixed an issue where the CIS peripheral would report wrong SDU sequence numbers upon receiving. (DRGN-24359)

  The issue would only happen if all the following conditions are met:

    * The subevent interval is large, or if the CIS is configured with interleaved packing.
    * There are scheduling conflicts.
* Fixed an issue where an application running on a nRF54L Series device would sometimes fail to receive an ACL packet after it had sent a packet on Coded PHY with S=2.
  The issue would only happen when the application explicitly asked to use the coding scheme S=2. (DRGN-23691)
* Fixed an issue where a CIS Peripheral would assert when receiving an invalid ``LL_CIS_REQ``.
  This would only happen if unframed PDUs were used. (DRGN-24706)
* Fixed a rare issue where the controller would assert when in a connection. (DRGN-24749)

  The issue would only happen if all the following conditions are met:

    * A feature requiring long control packets is enabled, for example, CIS, Sync Transfer, or Channel Sounding.
    * A short event length is used.
    * The data length is not updated
* Fixed an issue where the central would disconnect without sending a ``LL_TERMINATE_IND`` when the user sent the Disconnect HCI command.
  This issue occurred when the central was blocked by another higher-priority role for extended periods. (DRGN-24784)
* Fixed a rare assert when stopping a CIG or BIG.
  This issue would only occur when another CIG or BIG role was active at the same time. (DRGN-24938)
* Fixed a rare issue where the controller running on an nRF54 Series device would send a corrupted packet with a valid CRC.
  This could lead to sending a packet with an invalid MIC in the case of an encrypted connection.
  The issue would occur if the :kconfig:option:`CONFIG_FPU` and :kconfig:option:`CONFIG_FPU_SHARING` Kconfig options are enabled. (DRGN-24929)

nRF Connect SDK v2.9.0
**********************

Added
=====

* Production support for scanning and initiating at the same time. (DRGN-23824)
* :ref:`Experimental <nrf:software_maturity>` support for Channel Sounding step mode-3.
* :ref:`Experimental <nrf:software_maturity>` support for Channel Sounding multiple antenna elements.
* :ref:`Experimental <nrf:software_maturity>` support for the following Channel Sounding HCI commands:

    * LE CS Write Cached Remote Supported Capabilities
    * LE CS Write Cached Remote FAE Table
    * LE CS Remove Config

Changes
=======

* The vendor-specific Set Connection Event Trigger HCI command has been removed. (DRGN-23981)
* The documentation for the vendor-specific ISO Read TX Timestamp command has been updated to represent the returned value. (DRGN-23708)

Bug fixes
=========

* Fixed an issue where the CIS central running on an nRF53 Series device could set an invalid MIC when sending encrypted ISO packets. (DRGN-23776)
* Fixed a rare issue where the scanner may give a single advertising report with corrupted data when restarting scanning.
  The issue would only happen when the scanner received a long extended advertising packet that did not fit into a single advertising report and the scanning was stopped explicitly or through a timeout. (DRGN-23966)
* Fixed an issue where the CIS TX Power was set according to the LE Power Control state of the previous CIS in a CIG. (DRGN-21721)
* Fixed an issue where the BIS receiver running with FEM could enable the radio at the wrong time, causing the receiver to drop packets and lose sync. (DRGN-23891)
* Fixed an issue where the controller would raise Number Of Completed Packets events for a disconnected CIS. (DRGN-23869)

nRF Connect SDK v2.8.0
**********************

Added
=====

* Production support for the nRF54L Series. (DRGN-23325)
* Support for the LE Set Path Loss Reporting Parameters and LE Set Path Loss Reporting Enable HCI commands. (DRGN-17376)
* Support for generating connection anchor update event reports using the VS Conn Anchor Point Update Report Enable command.
  When enabled, one report is generated when the anchor point of a connection is updated.
  This information can be used to synchronize two applications running on a central and a peripheral device. (DRGN-22662)
* Vendor-specific command for triggering a peripheral task at the start of a radio event.
  See :c:func:`sdc_hci_cmd_vs_set_event_start_task`. (DRGN-20737)
* Support for the LE Set Default Subrate and LE Subrate Request HCI commands. (DRGN-19745)
* Support for ISO broadcaster handles in the :c:func:`sdc_hci_cmd_vs_zephyr_write_tx_power` and :c:func:`sdc_hci_cmd_vs_zephyr_read_tx_power` commands (DRGN-23441).
* :ref:`Experimental <nrf:software_maturity>` support for Channel Sounding (CS) on nRF54L Series devices.
  Currently, the |controller| only supports one subevent per event.
  The following HCI commands are now supported:

    * LE CS Read Local Supported Capabilities
    * LE CS Read Remote Supported Capabilities
    * LE CS Security Enable
    * LE CS Set Default Settings
    * LE CS Read Remote FAE Table
    * LE CS Create Config
    * LE CS Set Channel Classification
    * LE CS Set Procedure Parameters
    * LE CS Procedure Enable
    * LE CS Test
    * LE CS Test End

* The defines :c:macro:`SDC_PPI_CHANNELS_USED_MASK`, :c:macro:`SDC_DPPI_CHANNELS_USED_MASK`, :c:macro:`SDC_DPPIC10_CHANNELS_USED_MASK`, :c:macro:`SDC_DPPIC00_CHANNELS_USED_MASK`, :c:macro:`SDC_DPPIC020_CHANNELS_USED_MASK`, and :c:macro:`SDC_DPPIC030_CHANNELS_USED_MASK`.
  These represent the PPI resources used in the SoftDevice Controller.
* The defines :c:macro:`SDC_PPIB00_CHANNELS_USED_MASK`, :c:macro:`SDC_PPIB10_CHANNELS_USED_MASK`, :c:macro:`SDC_PPIB020_CHANNELS_USED_MASK`, and :c:macro:`SDC_PPIB030_CHANNELS_USED_MASK`.
  These represent the PPIB resources used in the SoftDevice Controller.

Changes
=======

* Removed support for running the SoftDevice Controller on the nRF54L15 PDK v0.7.0 and earlier. (DRGN-23325)
* Removed support for running the SoftDevice Controller on the Engineering A revision of the nRF54H20 SoC. (DRGN-23325)
* The ``VersNr`` field in the ``LL_VERSION_IND`` packet now contains the value ``0x0E`` to indicate compatibility with Bluetooth Core Specification v6.0 (DRGN-23211).
* The ``sdc_coex_adv_mode_configure`` API has been deprecated as it is not applicable to any supported coexistence interfaces. (DRGN-20876).
* The ``sdc_hci_cmd_vs_coex_priority_config`` and ``sdc_hci_cmd_vs_coex_scan_mode_config`` vendor-specific HCI commands have been removed as they are not applicable to any supported coexistence interfaces. (DRGN-20876)
* The vendor-specific Set Connection Event Trigger command has been deprecated.
  Users interested in similar functionality are encouraged to use the VS Set Event Start Task command instead. (DRGN-20737)
* Extended Connection Events are not re-enabled on HCI Reset.
  The state before HCI Reset is preserved, either the value of :kconfig:option:`CONFIG_BT_CTLR_SDC_CONN_EVENT_EXTEND_DEFAULT` or the most recent call to :c:func:`sdc_hci_cmd_vs_conn_event_extend`. (DRGN-22687)
* The paths to the library files for SoftDevice Controller and MPSL were changed to use the device family. (DRGN-21939)

    * ``cortex-m4`` changed to ``nrf52``
    * ``cortex-m33+nodsp`` changed to ``nrf53``
    * ``nrf54l15_cpuapp`` changed to ``nrf54l``
    * ``nrf54h20_cpurad`` changed to ``nrf54h``
* For a Synchronized Receiver, the priority of the first ``BN`` subevents of relevant BISes in a BIG event now have an elevated priority.
  This should improve reliability of ISO data being received by a Synchronized Receiver running alongside a role of lower priority.
  For more details, see the :ref:`scheduling_priorities_table` table.
* The SoftDevice Controller can now utilize more than 64K of memory buffer passed to :c:func:`sdc_enable`. (DRGN-22067)
* If LE Power Control is not being used, the TX power of CISes is now the same as for the corresponding ACL connection. (DRGN-23291)
* Generating the Number of Completed Packets event is now prioritized above all other events.
  The event is generated irrespective of the state of the Controller to Host data flow control. (DRGN-23284)
* When a link disconnects, the controller will now raise one or more Number Of Completed Packets events for data packets not ACKed by the peer device. (DRGN-23302)
* Isochronous roles may now produce HCI ISO data with SDUs containing the ``0b01`` packet status flag which indicates possibly invalid data.
  This is the case if the peer sends invalid data. (DRGN-23420)

Bug fixes
=========

* Fixed a rare assert that could happen when disabling a periodic advertising set with responses. (DRGN-22443)
* Fixed an issue where the length byte of the HCI packet could be incorrect.
  This could happen when the packet contained an LE BIG Sync Established event or LE BIG Complete event with status not equal to success. (DRGN-22441)
* Fixed an assert that could happen when in a connection where the peer device is transmitting on S8 Coded PHY.
  This issue was present in v2.6 and v2.7 releases. (DRGN-22652)
* Fixed an issue where the extended scanner would not generate a truncated advertising report after the coexistence interface aborted the reception of an ``AUX_CHAIN_IND`` packet. (DRGN-22686)
* Fixed a very rare issue where the controller stopped generating advertising reports.
  On nRF52 Series and nRF53 Series devices, this would happen at least one hour after the scanner started.
  On nRF54L and nRF54H Series devices, this would occur immediately after the scanner started. (DRGN-22678)

  It would only happen when one of the following applies:

    * There was another central-like scheduling activity running. Examples of roles with such activities are the ACL central, periodic advertiser, isochronous broadcaster and the CIS central.
      This activity was configured with an event length or event spacing equal or greater than the scan interval.
      This is typically only true for use cases where the application enables isochronous channels or uses very short scan windows.
    * The scanner was configured with scan window equal to scan interval (continuous scanning).
    * The central-like scheduling activity required less than 1 ms to complete at the point in time where the scanner started.
* Fixed a rare issue where the scanner would be stuck in the synchronizing state after failing to receive an ``AUX_ADV_IND`` packet.
  This could only happen when the corresponding ``ADV_EXT_IND`` packet contained a resolvable address, private address resolution is enabled, and the periodic advertising list is not used. (DRGN-22230)
* Fixed an issue where the controller could generate the LE Advertising Set Terminated event one event sooner than expected. (DRGN-22705)

  This could only happen when all of the following apply:

    * a non-zero Max_Extended_Advertising_Events parameter was used in the LE Set Extended Advertising Enable command.
    * other ongoing activities in the controller prevented the first advertising event from taking place when the advertising set was created.
* Fixed an issue where calling the :c:func:`sdc_hci_cmd_vs_zephyr_write_tx_power` function without the LE Power Control feature enabled could cause the controller to de-reference a NULL pointer. (DRGN-22930)
* Fixed an issue where the Central failed to receive the last packet in an isochronous event.
  This could only happen if the Connected Isochronous Stream Creation procedure was initiated by the host before the Encryption Start procedure completed. (DRGN-22879)
* Fixed an assert that could happen when using the coexistence interface. (DRGN-23002)

  This could happen when any of the following controller activities were ongoing:

    * Isochronous Broadcaster
    * Connected Isochronous channel in the peripheral role
    * Periodic Sync with Responses
* Fixed an issue where LE Power Control was not being used for CISes which are not the first CIS in a CIG. (DRGN-23291)
* Fixed an issue where the SoftDevice Controller in the peripheral role could terminate a connection due to a MIC failure during a valid encryption start procedure.
  This could only happen if the ``LL_ENC_RSP`` packet was corrupted due to on-air interference. (DRGN-23204)
* Fixed an issue where received unframed Isochronous SDUs were not reported to be a SDU interval apart.
  This could happen when the ISO interval is greater than the SDU interval and multiple SDUs can be received in a single ISO interval. (DRGN-23586)
* Fixed an issue where the sleep clock accuracy communicated to the peer was too inaccurate if MPSL was initialized with a low frequency clock accuracy better than 20ppm. (DRGN-23693)
* Fixed a rare issue in the controller that could lead to a bus fault. (DRGN-22036)

  This could only happen when all of the following conditions were met:

    * The host was too slow at pulling HCI events.
    * One or more HCI events had been masked in the controller.
    * The controller was raising ACL or ISO data to the host.

nRF Connect SDK v2.7.0
**********************

Added
=====

* Experimental support for scanning and initiating at the same time. (DRGN-19050)
* Vendor-specific HCI command to set the channel map for scanning and initiating.
  See :c:func:`sdc_hci_cmd_vs_scan_channel_map_set` (DRGN-19730).
* Vendor-specific HCI command to configure the scanner and initiator to either accept or reject extended advertising packets.
  See :c:func:`sdc_hci_cmd_vs_scan_accept_ext_adv_packets_set` (DRGN-21755).
* Vendor-specific HCI command to change the scheduling priorities.
  Currently, this only supports changing the priority of initiator activities on the auxiliary channels.
  Note that unless documented otherwise, any non-default priorities are not tested.
  This means that there is no guarantee that the controller works as intended when non-tested priorities are used.
  See :c:func:`sdc_hci_cmd_vs_set_role_priority` (DRGN-21226).

Changes
=======

* The |controller| will now schedule all scanner primary channel timing-events cooperatively even when the sum of the scan windows is less than the scan interval.
  If the |controller| is unable to schedule a full scan window for a long time, the scheduling priority will be raised to ensure a full window is scheduled.

  Generally, this change will result in either increased scanning time, or similar scanning time to before.
  In cases where there are many conflicting activities within the scan window, this change may result in reduced scanning time. (DRGN-19050)
* Scan windows are no longer limited to 16 seconds. (DRGN-19050)
* The deprecated structure members ``sdc_rand_source_t.rand_prio_low_get`` and ``sdc_rand_source_t.rand_prio_high_get`` have been removed.
  This change does not affect applications developed in the |NCS| context. (DRGN-20473)
* The HCI commands used to configure a scanner or initiator no longer return ``BT_HCI_ERR_INVALID_PARAM`` when the sum of scan windows is greater than the scan interval.
  Now the controller will truncate the scan windows so that the sum of the windows fit within the scan interval. (DRGN-21710)
* The vendor-specific Set Connection Event Trigger command can now be used with advertising sets. (DRGN-21665)
* The application can now configure the amount of RAM allocated for the RX ISO SDUs.
  The |controller| now uses the field ``rx_sdu_buffer_size`` in ``sdc_cfg_iso_buffer_cfg_t``.
  The macro :c:macro:`SDC_MEM_ISO_RX_SDU_POOL_SIZE` has been changed to take the maximum RX SDU size as an input.
  This change does not affect applications developed in the |NCS| context. (DRGN-21650)
* The application can now configure the amount of RAM allocated for the TX ISO SDUs.
  The fields ``tx_sdu_buffer_count`` and ``tx_sdu_buffer_size`` in ``sdc_cfg_iso_buffer_cfg_t`` are added.
  The fields ``tx_hci_buffer_count`` and ``tx_hci_buffer_size`` in ``sdc_cfg_iso_buffer_cfg_t`` are removed.
  The macros :c:macro:`SDC_MEM_ISO_TX_PDU_POOL_SIZE` and :c:macro:`SDC_MEM_ISO_TX_SDU_POOL_SIZE` replace :c:macro:`SDC_MEM_ISO_TX_POOL_SIZE`.
  This change does not affect applications developed in the |NCS| context. (DRGN-21650)
* The function :c:func:`sdc_soc_ecb_block_encrypt` has been removed.
  Using :file:`mpsl_ecb.h` is now recommended instead. (DRGN-21603)
* The ability to configure a periodic advertiser with subevents but without response slots has been removed.
  This is due to an errata to the Bluetooth Core Specification v5.4 no longer allowing this configuration. (DRGN-22189)

Bug fixes
=========

* Fixed an issue where an assert could happen if an initiator ran for more than 2147 seconds before connecting (DRGN-22163).
* Fixed an extremely rare race condition where using :c:func:`sdc_soc_ecb_block_encrypt` from an ISR could lead to encryption failures. (DRGN-21603)
* Fixed an issue where the vendor-specific ISO Read TX Timestamp command returned a timestamp that was 41 µs too small (DRGN-21605).
* Fixed an issue where an assert could happen if a CIS peripheral stopped receiving packets from the CIS central.
  This would only occur after the window widening reached at least half of the ISO interval in magnitude.
  Assuming worst case clock accuracies on both central and peripheral, this would correspond to 2.4, 3.7, and 4.9 seconds for ISO intervals of 5 ms, 7.5 ms, and 10 ms.
  This issue would not occur if the supervision timeout was set to a value smaller than the ones mentioned above (DRGN-21619).
* Fixed an issue where the peripheral waited for a link to time out when tearing down the connection.
  This happened when the central would acknowledge ``TERMINATE_IND`` in the same event as it was being sent (DRGN-21637).
* Fixed an issue where the |controller| would accept the HCI LE Set Random Address command while passive scanning had been enabled.
  The |controller| now returns the error code ``0x0D`` in this case. (DRGN-19050)
* Fixed an issue where a BIS Broadcaster would transmit invalid parameters in the BIG Info if a BIG was created with ``num_bis`` set to ``1`` and ``packing`` set to ``1`` (interleaved).
  This could happen with both the LL Create BIG and LL Create BIG Test commands (DRGN-21912).
* Fixed an issue with the controller-initiated autonomous LE Power Control Request procedure for Coded PHY that could lead to a disconnection. (DRGN-21923)
* Fixed an issue where the |controller| could assert if a BIS Receiver stops receiving packets from the BIS Broadcaster. (DRGN-21949)
* Fixed an issue where the |controller| could in some rare cases generate an LE Periodic Advertising Subevent Data Request for a subevent it did not have the memory capacity for. (DRGN-21839)
* Fixed an issue where an assert could happen if the peripheral received a connection update indication.
  This happened when the central used a wide receive window for the connection update, and both sent at the end of the receive window and sent a lot of data in the connection event with the connection update instant (DRGN-22024).
* Fixed an issue where the |controller| could assert when scanning or advertising on Coded PHY using SPI FEM on the nRF53 series. (DRGN-21962)

nRF Connect SDK v2.6.0
**********************

All the notable changes included in the |NCS| v2.6.0 release are documented in this section.

Added
=====

* Vendor-specific HCI command to read average RSSI calculated by LE Power Control.
  See :c:func:`sdc_hci_cmd_vs_read_average_rssi` (DRGN-17355).
* Vendor-specific HCI command to set the time between anchor points of central ACL connections with identical connection intervals.
  See :c:func:`sdc_hci_cmd_vs_central_acl_event_spacing_set` (DRGN-20796).
* Vendor-specific HCI command to set up (D)PPI tasks on radio events.
  See :c:func:`sdc_hci_cmd_vs_set_conn_event_trigger` (DRGN-20737).
* Vendor-specific HCI command to read the next connection event counter value.
  See :c:func:`sdc_hci_cmd_vs_get_next_conn_event_counter` (DRGN-20737).
* Vendor-specific HCI command to allow parallel connection establishment through initiating and periodic advertising with responses.
  See :c:func:`sdc_hci_cmd_vs_allow_parallel_connection_establishments` (DRGN-20823).
* Vendor-specific HCI command to  set the minimum value that will be used as maximum Tx octets for ACL connections.
  See :c:func:`sdc_hci_cmd_vs_min_val_of_max_acl_tx_payload_set` (DRGN-20819).
* Vendor-specific HCI command to read the ISO tx timestamp and packet sequence number of the SDU that the host previously provided.
  See :c:func:`sdc_hci_cmd_vs_iso_read_tx_timestamp` (DRGN-19283).
* Vendor-specific HCI command to change the time reserved for other roles in each ISO interval, used when selecting BIG parameters.
  See :c:func:`sdc_hci_cmd_vs_big_reserved_time_set` (DRGN-20891).
* Vendor-specific HCI command to change the time reserved for other roles in each ISO interval, used when selecting CIG parameters.
  See :c:func:`sdc_hci_cmd_vs_cig_reserved_time_set` (DRGN-21344).
* Vendor-specific HCI command to set the CIS subevent length.
  See :c:func:`sdc_hci_cmd_vs_cis_subevent_length_set` (DRGN-21362).

Changes
=======

* The LE Isochronous Channels feature is now :ref:`supported <nrf:software_maturity>` instead of experimental, both Connected Isochronous Streams and Broadcast Isochronous Streams.
  Unless mentioned otherwise, the |controller| supports the whole range of the allowed parameters.
  See the :ref:`softdevice_controller_limitations` section for known limitations.
* The controller now returns the error code ``0x12`` if the same subevent index is used multiple times in LE Set Periodic Advertising Subevent Data.
  This conforms to erratas ES23466 and ES23424. (DRGN-20736)
* The vendor-specific Set event length for ACL connections HCI command no longer sets the time between anchor points of central ACL connections with identical connection intervals. (DRGN-20796)
* The vendor-specific HCI commands :c:func:`sdc_hci_cmd_vs_set_auto_power_control_request_param` and
  :c:func:`sdc_hci_cmd_vs_set_power_control_apr_handling` have been replaced by
  :c:func:`sdc_hci_cmd_vs_set_power_control_request_params` (DRGN-17355).
* The controller now always returns the error code ``0x0D`` if a connection attempt is made while another is still pending.
  Previously, this was not the case if one connection attempt was through periodic advertising with responses while the other was through the initiator. (DRGN-20823)
* The scheduling priority for initiator events where the scan window is equal to the scan interval is lowered to the third scheduling priority.
  For other configurations of scan window and scan interval the priority is unchanged. (DRGN-20831)
* The vendor-specific Set event length for ACL connections HCI command now accepts values lower than 1250 us. (DRGN-20796)
* The scheduling priority for the scanner where the scan window is equal to the scan interval is lowered to the fourth scheduling priority.
  This will allow concurrent |BLE| roles to interrupt continuous scanning, but will reduce the time available for scanning.
  For other configurations of scan window and scan interval the priority is unchanged. (DRGN-19272)

  The scheduling priority for MPSL timeslots with normal priority and the 802.15.4 radio driver is lowered to the fifth scheduling priority.
  This is done to maintain the relative priority with them and continuous scanning. (DRGN-20488)
* Improved scheduling performance when receiving packets closely following an ``AUX_SYNC_IND`` that does not point to an ``AUX_CHAIN_IND``.
  The controller will attempt to prioritize the reception of such packets while still maintaining the periodic sync. (DRGN-19272)
* The functions :c:func:`rand_prio_low_get` and :c:func:`rand_prio_high_get` have been deprecated.
  They are no longer used by the SoftDevice Controller. (DRGN-20472)

Bug fixes
=========

* Fixed an issue where the LE Set Periodic Advertising Subevent Data command could fail when providing data at the same time as an ``AUX_SYNC_SUBEVENT_IND`` was sent. (DRGN-20762)
* Fixed an issue where a packet might not be received when sent at the instant of a Channel Map Update.
  This could happen when acting as Peripheral. (DRGN-20815)
* Fixed an assert that could happen if the LE Set Periodic Advertising Response Data command was issued more than once without fetching the Command Complete Event. (DRGN-20432)
* Fixed an issue where the controller would assert during cooperative active scanning or when running a cooperative initiator.
  This could happen when the controller was about to send a scan request or connect indication. (DRGN-20832)
* Fixed an issue where the nRF5340 DK consumed too much current while scanning.
  This could happen if the controller was running with TX power higher than 0 dB. (DRGN-20862)
* Fixed an assert that could happen if the Periodic Sync with Responses was terminated. (DRGN-20956)
* Fixed an issue where the controller stopped generating advertising reports.
  This could happen when the controller was running an extended cooperative scanner together with other activities, such as advertising or connection,
  while receiving data in an extended advertising event that used ``AUX_CHAIN_IND``. (DRGN-21020)
* Fixed an issue where the controller would stop sending ACL data packets to the host when controller to host flow control was enabled.
  This could happen when a disconnection occurred before the host had issued the Host Number of Complete Packets command for the remaining ACL data packets.
  Now the controller waits until after all ACL data packets have been acknowledged by the host before raising the Disconnection Complete event.
  The controller also validates the handles provided in the Host Number of Complete Packets command. (DRGN-21085)
* Fixed a rare issue where the scanner may assert when it schedules the reception of the next advertising packet. (DRGN-21253)

nRF Connect SDK v2.5.0
**********************

All the notable changes included in the |NCS| v2.5.0 release are documented in this section.

Added
=====

* Experimental support for isochronous channels, both Connected Isochronous Streams and Broadcast Isochronous Streams.
  The controller supports an ISO interval equal to the SDU interval, using unframed PDUs.
  The following HCI commands are now supported:

    * Read Connection Accept Timeout
    * Write Connection Accept Timeout
    * LE Read Buffer Size [v2]
    * LE Read ISO TX Sync
    * LE Set CIG Parameters
    * LE Set CIG Parameters Test
    * LE Create CIS
    * LE Remove CIG
    * LE Accept CIS Request
    * LE Reject CIS Request
    * LE Create BIG
    * LE Create BIG Test
    * LE Terminate BIG
    * LE BIG Create Sync
    * LE BIG Terminate Sync
    * LE Setup ISO Data Path
    * LE Remove ISO Data Path
    * LE ISO Transmit Test
    * LE ISO Receive Test
    * LE ISO Read Test Counters
    * LE ISO Test End
    * LE Set Host Feature
    * LE Read ISO Link Quality

* Experimental support for the Quality of Service (QoS) channel survey.
  See the :c:func:`sdc_hci_cmd_vs_qos_channel_survey_enable` function.
* Support for starting the scanner without setting scan parameters.
  Previously the controller would assert (DRGN-17623).
* Vendor-specific HCI command to enable utilization of remote APR on the local TX power when using LE Power Control.
  See :c:func:`sdc_hci_cmd_vs_set_power_control_apr_handling` (DRGN-17355).

Changes
=======

* Host now always receives LE Transmit Power Reporting Events.
  Previously, some events might not be received when remote and local power changes were applied to the same PHY simultaneously. (DRGN-18950)
* :c:func:`sdc_hci_cmd_put` and :c:func:`sdc_hci_cmd_vs_read_supported_vs_commands` functions are removed.
  This change does not affect applications developed in the |NCS| context. (DRGN-19281)
* When creating a connection or periodic advertiser, the controller will now attempt to select the interval so that it causes as few scheduling conflicts with existing periodic activities as possible.
  The selected interval is always in the range ``[interval_min, interval_max]``, where ``interval_min`` and ``interval_max`` are provided by the host.
  Previously, the controller always selected ``interval_max``.
* The ``SDC_CFG_TYPE_EVENT_LENGTH`` configuration is removed.
  An application must use the :c:func:`sdc_hci_cmd_vs_event_length_set` HCI command instead.
* The ChSel bit in a ``CONNECT_IND`` PDU will now match the ChSel bit in the ``ADV_IND`` PDU.
  Previously, this was always set to indicate channel selection algorithm 2. (DRGN-19115)
* The LE Power Control Request feature is now :ref:`supported <nrf:software_maturity>` instead of experimental. (DRGN-17499)
* :c:func:`sdc_soc_flash_write_async` and :c:func:`sdc_soc_flash_page_erase_async` functions are removed.
  This change does not affect applications developed in the |NCS| context. (DRGN-20451)
* When synchronizing to a periodic advertiser, the number of events skipped is restricted so that there are at least three opportunities to receive before timing out.
  Previously, only one opportunity to receive was guaranteed before timing out. (DRGN-20448)

Bug fixes
=========

* Fixed an issue where the continuous extended scanner would not be able to receive the ``AUX_ADV_IND`` packet if the time between the ``ADV_EXT_IND`` and ``AUX_ADV_IND`` was more than 840 μs (DRGN-19460).
* Fixed an issue where the stack would dereference a NULL pointer when a resolvable :c:enum:`own_address_type` was used in the HCI Le Extended Create Connection V2 command while the resolving list was empty (DRGN-19580).
* Fixed an issue where the HCI Reset command would not clear the channel map set by the host using the HCI Le Set Host Channel Classification command (DRGN-19623).
* Fixed a bug where the ``Peer_Address_Type`` parameter in the ``LE Connection Complete`` event was set to ``2`` or ``3`` in case the connection was established to a device whose address was resolved (DRGN-18411).
  The least significant bit of the ``Peer_Address_Type`` parameter was set correctly.
* Fixed an issue where the stack would assert if trying to set up more advertisers than there are available advertising sets (DRGN-20118).
* Fixed an issue where enabling an extended advertising set would assert in cases where a host-provided address was not needed and no address had been set up for the advertising set (DRGN-20085).
* Fixed an issue where the controller acting as a central would assert when receiving a non-compliant LL_PHY_RSP from a peer device (DRGN-20578).
* Fixed an issue that could occur when the Host Number of Complete Packets command was sent with a connection handle the controller had already raised a disconnect event for.
  The controller would return ``BT_HCI_ERR_INVALID_PARAM`` to the command, which would mean that the host could not return the buffer to the controller (DRGN-20654).

nRF Connect SDK v2.4.0
**********************

All the notable changes included in the |NCS| v2.4.0 release are documented in this section.

Added
=====

* Support for the vendor-specific HCI command: Set Compatibility mode for window offset (DRGN-18727).
* Support for Periodic Advertising with Responses (PAwR) Scanner (DRGN-18739).
* Support for LE Read and Write RF Path Compensation HCI commands (DRGN-10234 and DRGN-18202).
* Support for up to 255 addresses in the Filter Accept List (DRGN-18967).
* Support for configuring the Filter Accept List to have an arbitrary size (DRGN-18967).
* Support for sync handles in the :c:func:`sdc_hci_cmd_vs_zephyr_write_tx_power` and :c:func:`sdc_hci_cmd_vs_zephyr_read_tx_power` commands (DRGN-18805).
* Support for reading channel map updates that are not at the beginning of an ACAD (DRGN-19067).

Changes
=======

* The ``VersNr`` field in the ``LL_VERSION_IND`` packet now contains the value 0x0D to indicate compatibility with Bluetooth Core Specification v5.4 (DRGN-18624).
* Receiving a Periodic Advertisement Sync Transfer (PAST) with invalid parameters will now generate the ``LE Periodic Advertising Sync Transfer Received`` event when receiving PAST is enabled (DRGN-18803).
* Periodic advertiser is allocated from the Periodic Advertising with Responses (PAwR) Advertiser sets when :c:enum:`SDC_CFG_TYPE_PERIODIC_ADV_RSP_COUNT` is available.
  Otherwise, it is allocated from the Periodic Advertiser sets if :c:enum:`SDC_CFG_TYPE_PERIODIC_ADV_COUNT` is set (DRGN-18979).
* The controller now returns the error code ``0x0D`` instead of ``0x09`` if it has insufficient resources to handle more connections and the host tries to start a connectable advertiser or the controller receives the commands ``LE Extended Create Connection`` or ``LE Create Connection`` (DRGN-18944).
* Periodic Advertising with Responses (PAwR) Advertiser is supported (DRGN-18497).

Bug fixes
=========

* Fixed a rare issue where the controller could assert when starting a connectable advertiser or creating a connection too quickly after disconnection (DRGN-18714).
* Fixed an issue where the Periodic Advertisement Sync Transfer (PAST) sender may generate an incorrect ``SyncInfo`` field for periodic advertising intervals greater than 5 seconds (DRGN-18775).
* Fixed an issue where the Periodic Advertisement Sync Transfer (PAST) sender could assert if the associated periodic sync was not fully established (DRGN-18833).
* Fixed an issue where the controller would not deliver advertising reports for advertisements received when the scanner was close to timing out (DRGN-18651).
* Fixed lower TX power on the nRF21540 DK in connected state.
  This occurred when using MPSL FEM and manually configuring the radio power (DRGN-18971).
* Fixed an issue where the controller cannot synchronize to a periodic advertising train using the Periodic Advertising Sync Transfer procedure if it has previously tried to do it while it was already synchronized to the periodic advertising train (DRGN-19003).
* Fixed an issue where the peripheral would disconnect with DIFFERENT_TRANSACTION_COLLISION when a collision of a connection update and a PHY update occurs even when central asks for no change (DRGN-18840).
* Fixed a rare issue where the controller would assert when multiple instances of the same Bluetooth role were running and one of the instances was being stopped (DRGN-18424).
* Fixed an issue where the SoftDevice Controller would not accept an ``adv_handle`` provided in HCI commands with values above the configured number of advertising sets (DRGN-19058).
* Fixed an issue where the controller could assert while synchronized to a Periodic Advertiser (DRGN-18883).
* Fixed an issue where the controller fails to advertise using extended advertising in the first advertising event after an increase in advertising data payload (DRGN-19197).

nRF Connect SDK v2.3.0
**********************

All the notable changes included in the |NCS| v2.3.0 release are documented in this section.

Added
=====

* Support for enabling the receiving of Periodic Advertising Sync Transfer (PAST) using dedicated functions such as :c:func:`sdc_support_periodic_adv_sync_transfer_receiver_central` (DRGN-16995).
* Support for LE Request Peer SCA command HCI command (DRGN-17972).
* Support for Sleep Clock Accuracy Update control procedure (DRGN-17883).
* Support for Periodic Advertising with Responses (PAwR) Advertiser (experimental) (DRGN-18497).

Changes
=======

* Memory buffer provided to :c:func:`sdc_enable` must be 8 bytes aligned (DRGN-18090).

Bug fixes
=========

* Fixed an issue where the controller was using non-zero randomness for the first advertising event.
  This happened even after calling :c:func:`sdc_hci_cmd_vs_set_adv_randomness` with a valid ``adv_handle`` parameter (DRGN-18261).
* Fixed an issue where the controller would end up in the HardFault handler after receiving an invalid response to a scan request (DRGN-18358).
* Fixed a bug where the ``Peer_Address_Type`` parameter in the ``LE Connection Complete`` event was set to 2 or 3 in case the connection was established to a device which address was resolved (DRGN-18411).
  The least significant bit of the ``Peer_Address_Type`` parameter was set correctly.
* Fixed an issue where the stack could dereference a NULL pointer when starting a periodic advertiser (DRGN-18420).
* Fixed an issue where initiating Periodic Advertisement Sync Transfer (PAST) as advertiser may assert when the periodic advertisement train is not running (DRGN-18586).
* Fixed an issue where calling the :c:func:`bt_ctlr_set_public_addr` function before :c:func:`bt_enable` incorrectly failed to set the address (DRGN-18655).

nRF Connect SDK v2.2.0
**********************

All the notable changes included in the |NCS| v2.2.0 release are documented in this section.

Added
=====

* Support for Connection CTE Response in the angle of arrival (AoA) configuration (DRGN-17365).
* Support for LE Set Data Related Address Changes HCI command (DRGN-17919).
* Support for changing advertising randomness using :c:func:`sdc_hci_cmd_vs_set_adv_randomness` (DRGN-17872).
* Support for enabling the sending of Periodic Advertising Sync Transfer (PAST) using dedicated functions such as :c:func:`sdc_support_periodic_adv_sync_transfer_sender_central` (DRGN-17817).
* Experimental support for the LE Power Control Request feature (DRGN-17350).

Changes
=======

* The functions :c:func:`sdc_hci_evt_get` and :c:func:`sdc_hci_data_get` have been replaced by :c:func:`sdc_hci_get` (DRGN-17060).
* Scheduling performance when doing extended advertising and periodic advertising simultaneously has been improved on Coded PHY (DRGN-17819).

Bug fixes
=========

* Fixed an issue where the controller accepts an LL_PAUSE_ENC_REQ packet received on an unencrypted link (DRGN-17777).
* Fixed an issue where the controller accepts CONNECT_IND, AUX_CONNECT_REQ and CONNECTION_UPDATE_REQ packets with the ``connSupervisionTimeout`` value set to 0 (DRGN-17776).
* Fixed an issue where the controller would assert if trying to sync to a periodic advertiser with a sync timeout shorter than the periodic advertiser interval (DRGN-19744).
* Fixed an issue in MPSL where the controller would assert when a Bluetooth role was running (DRGN-17851).
* Fixed an issue in MPSL where the controller would abandon a link, causing a disconnect on the remote side (DRGN-18105).
* Fixed an issue where creating a periodic sync could in some cases erase periodic advertising reports for previously created syncs (DRGN-18089).

nRF Connect SDK v2.1.3
**********************

All the notable changes included in the |NCS| v2.1.3 release are documented in this section.

Bug fixes
=========

* Fixed an issue in MPSL where the controller would assert when a Bluetooth role was running (DRGN-17851).
* Fixed an issue in MPSL where the controller would abandon a link, causing a disconnect on the remote side (DRGN-18105).

nRF Connect SDK v2.1.2
**********************

All the notable changes included in the |NCS| v2.1.2 release are documented in this section.

Changes
=======

* On nRF53, the fix for Errata 158 is now applied.

nRF Connect SDK v2.1.0
**********************

All the notable changes included in the |NCS| v2.1.0 release are documented in this section.

Added
=====

* Support for changing the radio transmitter's default power level using :c:func:`sdc_default_tx_power_set` (DRGN-15903).
* Support for disabling or enabling peripheral latency using :c:func:`sdc_hci_cmd_vs_peripheral_latency_mode_set` (DRGN-15706).
* Stub version of :c:func:`sdc_hci_get` for getting all types of HCI packets from the Link Layer (DRGN-17060).
* Experimental support for generic coex (DRGN-17128).

Changes
=======

* When the SoftDevice Controller is used with the Front-End Module provided by the :ref:`mpsl`, the transmit power is expressed as the power on the antenna instead of the power of the SoC output.
  This allows dynamic gain control of the Front-End Module if the selected Front-End Module supports it.
  The default transmit power for Bluetooth LE activities does not change, so if the Front-End Module has an exemplary gain of +10 dB, the output power of the SoC will be decreased accordingly.
  To achieve higher output powers on the antenna, the user must call the appropriate API.
  For :c:func:`sdc_hci_cmd_vs_zephyr_write_tx_power` the transmit power is expressed as the maximum power on the antenna.
  The returned transmit power is the power on the antenna that can be achieved on the current SoC and Front-End Module.
  For :c:func:`sdc_hci_cmd_vs_zephyr_read_tx_power` the returned transmit power is the power on the antenna that can be achieved on the current SoC and Front-End Module.
  (KRKNWK-13714)
* Improved channel selection for secondary advertising packets (DRGN-17452).
* The extended advertiser will now always include the SyncInfo in the AUX_ADV_IND if there is a corresponding periodic advertiser, even if the offset cannot be represented (DRGN-16240).
* Split the function :c:func:`sdc_support_dle` into :c:func:`sdc_support_dle_central` and :c:func:`sdc_support_dle_peripheral`.
* Added functions :c:func:`sdc_support_phy_update_central` and :c:func:`sdc_support_phy_update_peripheral`, to enable change of PHY independently of the functions :c:func:`sdc_support_le_coded_phy` and :c:func:`sdc_support_le_2m_phy`
  These changes reduce the code size when using only central or peripheral role. (DRGN-17592)
* Applications may now configure fewer TX/RX buffers than the default.
  Note that this may lead to reduced throughput (DRGN-17651).
* The scanner is now scheduling cooperatively when the sum of scan windows is equal to the scan interval.
  This improves scheduling performance when scanning concurrently on multiple PHYs (DRGN-17754).
* Improved scheduling performance when synchronized to a periodic advertiser sending packets on Coded PHY (DRGN-17754).

Bug fixes
=========

* Fixed a HardFault that could occur when receiving legacy PDUs while using the periodic advertising synchronization functionality (DRGN-17656).
* Fixed an issue where the maximum data length capabilities were set to 27 bytes when the configured event length (:kconfig:option:`CONFIG_BT_CTLR_SDC_MAX_CONN_EVENT_LEN_DEFAULT`) was more than 65535 us (DRGN-17454).
* Fixed an issue where using the memory macros in :file:`sdc.h` with fewer TX/RX buffers than the default would report incorrect memory usage (DRGN-17651).
* Fixed an issue where the periodic advertiser sends its AUX_SYNC_IND 40 us later than indicated in the SyncInfo of the AUX_ADV_IND packet (DRGN-17710).
* Fixed an issue where the scanner would attempt to receive the first AUX_SYNC_IND 40 us later than indicated in the SyncInfo of the AUX_ADV_IND packet (DRGN-17710).

nRF Connect SDK v2.0.0
**********************

All the notable changes included in the |NCS| v2.0.0 release are documented in this section.

Added
=====

* Support for Peripheral-initiated Feature Exchange.
* Vendor-specific HCI commands to set the priority and scan mode of Wi-Fi coexistence.
  See :c:func:`sdc_hci_cmd_vs_coex_priority_config` and :c:func:`sdc_hci_cmd_vs_coex_scan_mode_config` (DRGN-16518).
* Support for periodic advertising intervals larger than ten seconds (DRGN-16873).
* Support for periodic sync timeouts larger than 128 seconds (DRGN-16434).
* The :c:func:`sdc_support_ext_central` function that makes the extended initiator role configurable (DRGN-16392).
* Support for connectionless angle of arrival (AoA) transmitter (DRGN-16588).
  The following HCI commands are now supported (DRGN-16713):

    * LE Set Connectionless CTE Transmit Parameters
    * LE Set Connectionless CTE Transmit Enable
    * LE Read Antenna Information

* Support for Periodic Advertising ADI (DRGN-16759).
* The ``nak_count`` field into QoS Connection event reports that counts the number of received Negative Acknowledges from the peer during the connection event.
  See ``sdc_hci_subevent_vs_qos_conn_event_report_t`` (DRGN-17183).
* The ``sdc_coex_adv_mode_configure`` API to configure the behavior of the advertiser when using the coexistence interface (DRGN-16585).

Changes
=======

* Update public API terms to Bluetooth Core Specification v5.3 (DRGN-16271)

    * :c:macro:`SDC_DEFAULT_MASTER_COUNT` has been renamed to :c:macro:`SDC_DEFAULT_CENTRAL_COUNT`.
    * :c:macro:`SDC_DEFAULT_SLAVE_COUNT` has been renamed to :c:macro:`SDC_DEFAULT_PERIPHERAL_COUNT`.
    * :c:macro:`SDC_MEM_PER_MASTER_LINK` has been renamed to :c:macro:`SDC_MEM_PER_CENTRAL_LINK`.
    * :c:macro:`SDC_MEM_PER_SLAVE_LINK` has been renamed to :c:macro:`SDC_MEM_PER_PERIPHERAL_LINK`.
    * :c:macro:`SDC_MEM_MASTER_LINKS_SHARED` has been renamed to :c:macro:`SDC_MEM_CENTRAL_LINKS_SHARED`.
    * :c:macro:`SDC_MEM_SLAVE_LINKS_SHARED` has been renamed to :c:macro:`SDC_MEM_PERIPHERAL_LINKS_SHARED`.
    * :c:enumerator:`SDC_CFG_TYPE_MASTER_COUNT` has been renamed to :c:enumerator:`SDC_CFG_TYPE_CENTRAL_COUNT`.
    * :c:enumerator:`SDC_CFG_TYPE_SLAVE_COUNT` has been renamed to :c:enumerator:`SDC_CFG_TYPE_PERIPHERAL_COUNT`.
    * :c:member:`sdc_cfg_t.master_count` has been renamed to :c:member:`sdc_cfg_t.central_count`.
    * :c:member:`sdc_cfg_t.slave_count` has been renamed to :c:member:`sdc_cfg_t.peripheral_count`.
    * :c:func:`sdc_support_master` has been renamed to :c:func:`sdc_support_central`.
    * :c:func:`sdc_support_slave` has been renamed to :c:func:`sdc_support_peripheral`.

* HCI interface was updated according to Bluetooth Core Specification v5.3.
  For a list of the original terms and names and their replacements, refer to `Appropriate Language Mapping Table`_.
* The scanner now waits until the host has pulled the previous event's periodic advertising reports before enqueuing a report for the next event. Note that this does not apply to single-PDU periodic advertising events (DRGN-16920).
* The binary size of an application using the scanner but not the central role is decreased (DRGN-16392).
* The functions :c:func:`sdc_support_scan` and :c:func:`sdc_support_ext_scan` can no longer be called together with :c:func:`sdc_support_central` (DRGN-16392).
* Removed support for running the SoftDevice Controller on the nRF5340 PDK (DRGN-15174).
* The ``VersNr`` field in the ``LL_VERSION_IND`` packet now contains the value 0x0C to indicate compatibility with Bluetooth Core Specification v5.3 (DRGN-16109).
* The ``sdc_hci_subevent_vs_qos_conn_event_report_t`` structure has been redefined (DRGN-17183).

Bug fixes
=========

* Fixed an issue where Advertiser Address Type in the LE Periodic Advertising Sync Established event was never set to 0x02 or 0x03, even if the advertiser's address was resolved (DRGN-17110).
* Fixed an issue where Advertiser Address Type was not set in the LE Periodic Advertising Sync Established event when using the Periodic Advertiser List (DRGN-17110).
* Fixed an issue where setting advertiser radio output power using the vendor-specific HCI command Zephyr Write TX Power Level returned ``Unknown Advertiser Identifier (0x42)``.
* Fixed an issue where reading advertiser radio output power using the vendor-specific HCI command Zephyr Read TX Power Level returned ``Unknown Advertiser Identifier (0x42)``.
* Fixed an issue where an assert could occur if :c:func:`sdc_disable` was called while a Bluetooth role was running (DRGN-16515).
* Fixed an issue where the advertiser would incorrectly set Offset Adjust in the SyncInfo when the offset to the ``AUX_SYNC_IND`` is large (DRGN-16887).
* Fixed an issue where issuing a legitimate connection update could result in an ``BT_HCI_ERR_INVALID_PARAM`` error (DRGN-17324).
* Fixed an issue where connecting to the same device using a different address got denied as a duplicate connection (DRGN-17232).

nRF Connect SDK v1.9.0
**********************

All the notable changes included in the |NCS| v1.9.0 release are documented in this section.

Added
=====

* Added support for Periodic Advertising for production for nRF52 Series.
* Added support for a vendor-specific HCI command setting the periodic advertising event length (DRGN-16513).
* Added ``SDC_CFG_TYPE_PERIODIC_ADV_LIST_SIZE`` to allow the application to configure the size of the periodic advertiser list (DRGN-16357).

Bug fixes
=========

* Fixed an issue on the nRF53 Series where an assert could occur when connected as a peripheral, and the RC oscillator is used as the Low Frequency Clock source (DRGN-16808).

nRF Connect SDK v1.8.0
**********************

All the notable changes included in the |NCS| v1.8.0 release are documented in this section.

Added
=====

* Added experimental support for Periodic Advertising.
  Use :c:func:`sdc_support_le_periodic_adv` or :c:func:`sdc_support_le_periodic_sync` or both to enable this feature.

  * ``SDC_CFG_TYPE_PERIODIC_ADV_COUNT`` can be used to set the number of periodic advertisers.
  * ``SDC_CFG_TYPE_PERIODIC_SYNC_COUNT`` can be used to set the number of synchronizations to periodic advertisers.
  * ``SDC_CFG_TYPE_PERIODIC_SYNC_BUFFER_CFG`` can be used to configure the number of periodic synchronization report buffers.

  The following HCI commands are now supported (DRGN-11505):

    * LE Set Periodic Advertising Data
    * LE Set Periodic Advertising Enable
    * LE Set Periodic Advertising Parameters
    * LE Periodic Advertising Create Sync
    * LE Periodic Advertising Create Sync Cancel
    * LE Periodic Advertising Terminate Sync
    * LE Add Device To Periodic Advertiser List
    * LE Remove Device From Periodic Advertiser List
    * LE Clear Periodic Advertiser List
    * LE Read Periodic Advertiser List Size
    * LE Set Periodic Advertising Receive Enable

Changes
=======

* The default advertising data size is now 31 bytes, even for extended advertising (DRGN-16209).
  ``SDC_CFG_TYPE_ADV_BUFFER_CFG`` can be used to change the maximum buffer size before enabling the controller.
  The required memory for an advertising set with a given advertising data size will then be returned by ``SDC_MEM_PER_ADV_SET``.
* The type ``sdc_cfg_scan_buffer_cfg_t`` is replaced with ``sdc_cfg_buffer_count_t``.
* The controller will now prevent establishing a connection to a device it is already connected to (DRGN-15989).

Bug fixes
=========

* Fixed an issue where the active scanner could assert when performing extended scanning on Coded PHY with a full whitelist (DRGN-16113 and DRGN-16013).
* Fixed an issue where extended advertising reports with advertising data with length 228 were lost (DRGN-16341).
* Fixed an issue where the peripheral would always listen on data channel 0 if the initiator sent a connection request with all channels marked as bad (DRGN-16394).
* Fixed an issue where an assert may occur when switching from a faster to a slower PHY (DRGN-15547).
  The assert would only occur when:

  * :c:union:`sdc_cfg_t` with :c:member:`event_length` is set to less than 2500 us and the PHY is updated from 2M to 1M, or from either 1M or 2M to Coded PHY.
  * :c:union:`sdc_cfg_t` with :c:member:`event_length` is set to less than 7500 us and a PHY update to Coded PHY is performed.

* Fixed an issue where the host callback was called after an advertising event even if there were no events generated (DRGN-16405).
* Fixed an issue where a MPU fault may occur when switching between extended and legacy advertising (NCSIDB-572).

nRF Connect SDK v1.7.0
**********************

All the notable changes included in the |NCS| v1.7.0 release are documented in this section.

Added
=====

* Added ``SDC_CFG_TYPE_SCAN_BUFFER_CFG`` to allow the application to configure the number of scan buffers (DRGN-15899).
* Added ``SDC_CFG_TYPE_ADV_BUFFER_CFG`` to allow the application to configure the maximum advertising buffer size (DRGN-15661).

Changes
=======

* The ``Direct_Address_Type`` and the ``Direct_Address`` in extended advertising reports are updated to reflect the latest BLE specification.
  See Specification errata 14566 and 15752 (DRGN-15927).
* The scanner is now scheduling cooperatively when the scan window is equal to the scan interval.
  This improves the performance in the case of Bluetooth Mesh applications (DRGN-13146).
* Support for radio front-end module (FEM) in nRF53 Series, based on the :ref:`mpsl_fem` (DRGN-14908).
* The application must now call the APIs prefixed with ``sdc_support_`` before calling :c:func:`sdc_cfg_set` (DRGN-15899).

Bug fixes
=========

* Fixed an issue where the scanner did not check that the scan window was smaller than the scan interval (DRGN-15586).
* Fixed an issue where the channel map provided by the "LE Host Set Channel Classification" HCI command was not always applied on the secondary advertising channels (DRGN-15695).
* Fixed an issue on the nRF53 Series where an assert could occur while scanning using legacy commands (DRGN-15852).
* Fixed an issue on the nRF53 Series where the scanner could generate corrupted advertising reports (DRGN-15852).
* Fixed an issue where the ``mpsl_tx_power_channel_map_set()`` API would not work on peripheral-only or central-only configurations (DRGN-16091).
* Fixed an issue where an assert may occur when legacy advertiser is used after "HCI LE Clear Advertising Sets" (DRGN-15993).
* Fixed an issue where an assert could occur when in LLPM mode and the connection interval was more than 1 ms (DRGN-16079).

nRF Connect SDK v1.6.0
**********************

All the notable changes included in the nRF Connect SDK v1.6.0 release are documented in this section.

Added
=====

* Added support for multiple advertising sets (DRGN-15426).
* Added radio front-end module (FEM) support, based on the :ref:`mpsl_fem` (nRF52 Series only) (DRGN-11059).
* Added support for the vendor-specific HCI command: Read Supported Vendor Specific Commands (DRGN-13763).
* Added support for the vendor-specific HCI command: Zephyr Read Key Hierarchy Roots (DRGN-13237).
* Added support for nRF5340, which was previously only supported for evaluation purposes (DRGN-8639).

Changes
=======

* Moved permanent limitations from the :ref:`nrf:known_issues` page to :ref:`softdevice_controller_limitations`.
* Increased the maximum supported radio output power on nRF53 Series devices from 0 dBm to 3 dBm.
  If the output power is above 0 dBm, NRF_VREQCTRL->VREGRADIO.VREQH is set (DRGN-15476).
* Reduced ``SDC_DEFAULT_RX_PACKET_COUNT`` from 3 to 2. Now the controller can achieve full throughput with only two RX buffers (DRGN-7696).
* Decoupled the controller from the random number generator (DRGN-12507).
  This functionality must now be provided by the user.
  The user must provide ``rand_prio_low_get()``, ``rand_prio_high_get()`` and ``rand_poll()`` through the newly introduced :c:func:`sdc_rand_source_register()`.
  These functions can be mapped to the Zephyr Entropy APIs:

    * ``rand_prio_low_get()`` <-> ``entropy_get_entropy_isr()`` (``*_isr()`` for nonblocking behavior)
    * ``rand_prio_high_get()`` <-> ``entropy_get_entropy_isr()``
    * ``rand_poll()`` <-> ``entropy_get_entropy()``

Bug fixes
=========

* Fixed an issue where a slave connection could disconnect prematurely if there were scheduling conflicts with other roles (DRGN-15469).
* Fixed an issue where the channel map provided by the LE Host Set Channel Classification HCI command was not applied on the secondary advertising channels (DRGN-13594).
* The SoftDevice Controller can now be qualified on nRF52832 (DRGN-15382).
* Fixed an issue where setting a legacy advertiser's scan response data using extended advertising HCI commands corrupted the advertising data (DRGN-15465).
* Fixed an issue where, in rare cases, an assert could occur when receiving a packet as a slave.
  This could only occur after performing a data length procedure on Coded PHY (DRGN-15251).
* Fixed an issue where "HCI Read RSSI" would always return a Command Disallowed (0x0C) error code (DRGN-15310).
* Fixed an issue where setting radio output power using the vendor-specific HCI command Zephyr Write TX Power Level returned ``Unsupported Feature or Parameter value (0x11)``.
  Now the controller will select an output power level that is lower or equal to the one requested.
  The command returns success and the selected power level (DRGN-15369).
* Fixed an issue where an assert could occur when running an extended advertiser with maximum data length and minimum interval on Coded PHY.
  The assert would only occur if there were scheduling conflicts (DRGN-15694).
* Fixed an issue where a connectable or scannable advertiser ends with sending a packet without listening for the CONNECT_IND, AUX_CONNECT_REQ, and SCAN_REQ (DRGN-15484).
* Fixed an issue where an extended advertiser with limited duration may time out after the first primary channel packet in the last advertising event (DRGN-10367).
* Fixed an issue where the coding scheme provided by the LE Set PHY HCI Command was ignored after a remote initiated PHY procedure (DRGN-15531).
* Fixed an issue where the controller may still have pending events after :c:func:`sdc_hci_evt_get()` returns false.
  This would only occur if the host has masked out events (DRGN-15758).
* Fixed an issue where the extended scanner generated reports containing truncated data from a chained advertising PDU (DRGN-13338).

nRF Connect SDK v1.5.0
**********************

All the notable changes included in the nRF Connect SDK v1.5.0 release are documented in this section.

Added
=====

* Added :c:func:`sdc_support_ext_scan` which makes support for extended scanning configurable (DRGN-14902).
* Added :c:func:`sdc_support_ext_adv` which makes support for extended advertising configurable (DRGN-14914).
* Added support for the vendor-specific HCI command: Zephyr Read Chip Temperature (DRGN-13769).
* Added support for the vendor-specific HCI command: Zephyr Read Tx Power (DRGN-15250).

Changes
=======

* Renamed and reconfigured the libraries (DRGN-15118).
  Refer to the README for their corresponding supported feature sets.
  The new names are now:

    * ``libsoftdevice_controller_peripheral.a``
    * ``libsoftdevice_controller_central.a``
    * ``libsoftdevice_controller_multirole.a``

* All libraries are now compatible with all platforms within a given family (DRGN-15118).

Bug fixes
=========

* Fixed an issue where the application could not immediately restart a connectable advertiser after a high duty cycle advertiser timed out (DRGN-13029).
* Fixed an issue where a directed advertiser used a resolvable address as the ``TargetA`` when the local device address was set to public or random device address (DRGN-13921).
* Fixed an issue where "HCI LE Set Extended Advertising Parameters" should have returned "Packet Too Long (0x45)" when the advertising set was already configured with data that was longer than it could fit within the advertising interval.
  Previously, the advertising data was cleared every time the advertising set was configured (DRGN-14008).
* Fixed an issue where the link would disconnect with reason ``LMP Response Timeout (0x22)``.
  This would occur if the "HCI LE Long Term Key Request event" was disabled and the slave received an encryption request (DRGN-15226).
* Fixed an issue where the LL control procedures LE start encryption and LE connection parameter update could not be initiated at the same time (DRGN-11963).
* Fixed an issue where the generation of QoS Connection event was not disabled after an HCI reset (DRGN-15291).

Known issues
============

See the :ref:`nrf:known_issues` page in |NCS| for the list of known issues and limitations for this release.

nRF Connect SDK v1.4.0
**********************

All the notable changes included in the nRF Connect SDK v1.4.0 release are documented in this section.

Added
=====

* Added Read Transmit Power Level command (DRGN-12236).
* Added LE Read Transmit Power command (DRGN-12236).
* Added LE Read Advertising Physical Channel Tx Power command (DRGN-12238).
* Added support for setting the event length of a connection. See :c:func:`hci_vs_cmd_event_length_set` (DRGN-12696).
* Added Set Controller to Host Flow Control command (DRGN-13331).
* Added Host Buffer Size command (DRGN-13331).
* Added Host Number of Complete Packets command (DRGN-13331).
* Added support for the vendor-specific HCI command: Zephyr Write BD Addr (DRGN-14511).
* Added LE Read PHY command (DRGN-14664).
* Added APIs for every supported HCI command (DRGN-13723).
* Added :c:func:`sdc_support_adv` which makes the advertising state configurable (DRGN-14759).
* Added :c:func:`sdc_support_slave` which makes the slave role configurable (DRGN-14759).
* Added :c:func:`sdc_support_scan` which makes the scanning state configurable (DRGN-14759).
* Added :c:func:`sdc_support_master` which makes the master role configurable (DRGN-14759).

Changes
=======

* When linking the final binary, the image size is reduced. Only the requested features are included.
  See :c:func:`sdc_support_adv` and similar APIs for more details.
* When LLPM mode is enabled, the connection event length is now no longer implicitly set to 1 ms (DRGN-12696).
* When the connection interval is an LLPM connection interval, that is, below 7.5 ms, link-layer procedures with an instant will use an instant larger than 6 connection events (DRGN-14379).
* The nRF Bluetooth LE Controller was renamed to SoftDevice Controller (DRGN-14283).
  APIs are updated accordingly:

  * BLE_CONTROLLER -> SDC
  * ble_controller -> sdc
  * HCI APIs are now prefixed with sdc

* The name of the library file was changed to :file:`libsoftdevice_controller.a` (DRGN-14283).
* SoC APIs have been renamed (DRGN-14283):

  * ble_controller_flash_write -> sdc_soc_flash_write_async
  * ble_controller_flash_page_erase -> sdc_soc_flash_page_erase_async
  * ble_controller_rand_vector_get -> sdc_soc_rand_vector_poll
  * ble_controller_rand_vector_get_blocking -> sdc_soc_rand_vector_get
  * ble_controller_ecb_block_encrypt -> sdc_soc_ecb_block_encrypt

* Vendor-specific HCI APIs have been renamed (DRGN-14701):

  * HCI_VS_OPCODE   -> HCI_OPCODE_VS
  * HCI_VS_SUBEVENT -> HCI_SUBEVENT_VS
  * hci_vs_cmd      -> hci_cmd_vs

Bug fixes
=========

* Fixed an issue in the master role which could cause disconnects if there were scheduling conflicts while doing control procedures with an instant (DRGN-11222).

Known issues and limitations
============================

See the :ref:`nrf:known_issues` page in |NCS| for the list of known issues and limitations for this release.

nRF Connect SDK v1.3.0
**********************

All the notable changes included in the nRF Connect SDK v1.3.0 release are documented in this section.

Added
=====

* Added Read Authenticated Payload Timeout command.
* Added Write Authenticated Payload Timeout command.
* Added Set Event Mask command.
* Added Set Event Mask Page 2 command.
* Added :c:func:`ble_controller_support_le_2m_phy` which makes LE 2M PHY support configurable.
* Added :c:func:`ble_controller_support_le_coded_phy` which makes LE Coded PHY support configurable.
* Added LE Read Supported States command.
* Added LE Set Advertising Set Random Address command.
* Added LE Remove Advertising Set command.
* Added LE Clear Advertising Sets command.
* Added support for the vendor-specific HCI command: Zephyr Read Version Information.
* Added support for the vendor-specific HCI command: Zephyr Read Supported Commands.
* Added support for the vendor-specific HCI command: Zephyr Read Static Addresses.
* Added support for the vendor-specific HCI command: Zephyr Write TX Power Level (per Role/Connection).

Changes
=======

* ``HCI_VS_SUBEVENT_CODE_QOS_CONN_EVENT_REPORT`` was renamed to ``HCI_VS_SUBEVENT_QOS_CONN_EVENT_REPORT``.
* ``hci_vs_evt_qos_conn_event_report_t`` was renamed to ``hci_vs_subevent_qos_conn_event_report_t``.
* ``hci_vs_cmd_zephyr_read_supported_commands_return_t`` was converted from a struct to a union.
  The content remains the same.
* The VersNr field in the LL_VERSION_IND packet now contains the value 0x0B to indicate Bluetooth Core Specification v5.2 compliance.
* The previously implemented Vendor Specific HCI command opcodes are now offset with 0x100.
* The previously implemented Vendor Specific HCI event codes are now offset with 0x80.
* When the controller receives an unknown command, it will raise ``Command Status event`` instead of ``Command Complete event``.
* When in slave latency, the controller now picks up data from the host for transmission earlier than it used to.
* In the LE Extended Advertising Report, the Direct Address Type values 0x02, 0x03, and 0xFE will only be used when the Scanning Filter Policy is equal to 0x02 or 0x03 and TargetA is a resolvable private address.
  If the address is resolved, then the Direct Address Type will contain the same value as the Own Address Type parameter of the command LE Set Extended Scan Parameters.
  This follows the Bluetooth Core Specification v5.2.
* On nRF53, the fix for Errata 16 is now applied.

nRF Connect SDK v1.2.0
**********************

All the notable changes included in the nRF Connect SDK v1.2.0 release are documented in this section.

Added
=====

* Added :c:func:`ble_controller_support_dle` which makes LE Data Length Extension support configurable.
* Added preliminary support for the S140 variant with the nRF5340 device.
  The Bluetooth LE Controller for nRF5340 supports the same feature set as its nRF52 Series counterpart.
  The following library has been added:

  * :file:`ble_controller/lib/cortex-m33+nodsp/soft-float/libble_controller_s140.a`

Changes
=======

* :c:func:`mpsl_init` is no longer called by :c:func:`ble_controller_init`.
  Application is therefore responsible for calling :c:func:`mpsl_init`, and it must be done before :c:func:`ble_controller_init` is called.
* Clock configuration parameters are now contained in :c:type:`mpsl_clock_lfclk_cfg_t` instead of :c:type:`nrf_lf_clock_cfg_t`, and must be provided to :c:func:`mpsl_init` instead of :c:func:`ble_controller_init`.
* Clock accuracy must now be specified in parts per million (ppm) instead of the previous enum value.
* The IRQ line to pend for low priority signal processing must be provided to :c:func:`mpsl_init` instead of :c:func:`ble_controller_init`.
* The application must call :c:func:`mpsl_low_priority_process` instead of :c:func:`ble_controller_low_prio_tasks_process` to process low priority signals.
* :c:func:`mpsl_uninit` is no longer called by :c:func:`ble_controller_disable`.
  Application must therefore call :c:func:`mpsl_uninit` after :c:func:`ble_controller_disable` to uninitialize MPSL.
* Interrupt handler APIs for the following peripherals are moved to MPSL: RADIO, RTC0, TIMER0, and POWER_CLOCK.
* High-frequency clock API (``ble_controller_hf_clock_...``) is removed.
  Use the corresponding API in MPSL instead.
* Temperature API (:c:func:`ble_controller_temp_get`) is removed.
  Use the corresponding API in MPSL instead.
* Timeslot API is removed.
  Use the corresponding API in MPSL instead.
* Version numbers have been removed from the libraries.

Bug fixes
=========

* Fixed an issue where the application could not immediately restart a connectable advertiser after a high duty cycle advertiser timed out.
* Fixed an issue where a control packet could be sent twice even after the packet was ACKed.
  This would only occur if the radio was forced off due to an unforeseen condition.
* Fixed an issue in HCI LE Set Extended Scan Enable where ``UNSUPPORTED_FEATURE`` was returned when duplicate filtering was enabled.
* Fixed an issue in HCI LE Set Advertising Parameters where ``UNSUPPORTED_FEATURE`` was returned when ``secondary_max_skip`` was set to a non-zero value.
  This issue occurred when sending a packet on either LE 1M or LE 2M PHY after receiving or transmitting a packet on
  LE Coded PHY.
  If this occurred while performing a Link Layer Control Procedure, the controller could end up retransmitting
  an ACKed packet, resulting in a disconnect.
* Fixed an issue where an assert could occur when receiving a packet with a CRC error after performing a data length procedure on Coded PHY.
* Fixed an issue where an assert occurred when setting a secondary PHY to 0 when using HCI LE Set Extended Advertising Parameters.
  This issue occurred when the advertising type was set to legacy advertising.

nRF Bluetooth LE Controller 0.3.0-3.prealpha
********************************************

All the notable changes included in this release are documented in this section.

Added
=====

* Added support for nRF52833.

Bug fixes
=========

* Fixed an issue where :c:func:`hci_data_get` could return "No data available" when there was data available.
  This issue would only occur when connected to multiple devices at the same time.

nRF Bluetooth LE Controller 0.3.0-2.prealpha
********************************************

All the notable changes included in this release are documented in this section.

Bug fixes
=========

* Fixed an issue where an assert occurred when the host issued LE Write Suggested Default Data Length.

nRF Bluetooth LE Controller 0.3.0-1.prealpha
********************************************

All the notable changes included in this release are documented in this section.

Added
=====

* Increased the number of supported SoC and library combinations.
* Added API for estimating the dynamic memory usage returned by :c:func:`ble_controller_cfg_set`.
* Added a new header :file:`ble_controller_hci_vs.h` that exposes definitions of
  Vendor-Specific HCI commands and events.
* Added support for connection intervals less than the standard minimum of 7.5 ms.
  Note that this is a proprietary feature that is not Bluetooth compliant.
  This proprietary feature is named 'Low Latency Packet Mode (LLPM)'.
* Added support for enabling or disabling connection event length extension.
  When disabled, the maximum connection event length is set by ``ble_controller_cfg_event_length_t::event_length_us``.
  When enabled, the maximum connection event length is determined by the connection interval.
* Added support for generating QoS Connection event reports.
  When enabled, one report is generated with every connection event.
  The report contains information that can be used to change the Bluetooth LE channel map.

Bug fixes
=========

* Fixed an issue where the "HCI Read Local Supported Commands" command did not indicate support for the "HCI LE Set Privacy Mode" command.
* Fixed an issue where an ASSERT occurred when setting advertising data after HCI Reset without setting advertising parameters.
* Fixed an issue where an ASSERT occurred when writing to flash.
* Fixed an issue where a directed advertiser could time out without sending a packet on air.

Changes
=======
* The ``VersNr`` field in the LL_VERSION_IND packet now contains the value 0x0A to indicate Bluetooth Core Specification v5.1 compatibility.
* Bluetooth Core Specification Erratum #10750 is incorporated.
  The LE Data Length Change event will now be raised when switching to and from Coded PHY.
  On-air behavior has not changed.
* Bluetooth Core Specification Erratum #10818 is incorporated.
  The controller now allows HCI ACL data packets with a 0-length payload but does not transmit anything until receiving the next non-zero continuation fragment.
* Cleaned up invalid Doxygen comments.


nRF Bluetooth LE Controller 0.2.0-4.prealpha
********************************************

* Added a workaround to block the host from sending HCI commands when a shared command is in progress.


nRF Bluetooth LE Controller 0.2.0-3.prealpha
********************************************

Fixed a bug causing an assert in ``ble_controller_soc.c:29``.

nRF Bluetooth LE Controller 0.2.0-2.prealpha
********************************************

Minor documentation fixes.

Changes
=======

* Added names to nested structs and unions in :file:`timeslot.h` as a workaround for a Sphinx documentation build issue.
* Fixed internal links to functions and files.

nRF Bluetooth LE Controller 0.2.0-1.prealpha
********************************************

Updated Bluetooth LE Controller with bug fixes and updated APIs.

Added
=====

* Added API for fetching build revision information.
* Added :c:func:`ble_controller_rand_vector_get_blocking` as a blocking call to get a vector of random bytes.
* Added API to get Bluetooth LE Controller build revision: :c:func:`ble_controller_build_revision_get`.
* Added separate :c:func:`ble_controller_init` API.

Bug fixes
=========

Fixed an issue in HCI control flow that severely limited Bluetooth LE throughput.

Changes
=======
* Moved ``fault_handler`` and ``p_clk_cfg`` from :c:func:`ble_controller_enable` to :c:func:`ble_controller_init`.
* Changed :c:func:`ble_controller_process_SWI5_IRQ` to be IRQ independent.
  The generic :c:func:`ble_controller_low_prio_tasks_process` is used instead and SWI5 is no longer reserved.
* Aligned naming for Bluetooth LE Controller configuration names.
* Made minor changes to existing API.
* Improved API documentation.

nRF Bluetooth LE Controller 0.1.0-2.prealpha
********************************************

No change to library files.

Added
=====

* Added the headers necessary to utilize the timeslot API.


nRF Bluetooth LE Controller 0.1.0-1.prealpha
********************************************

Initial release.

Added
=====

* Added the following ble_controller_nrf52_0.1.0-1.prealpha library variants, each in soft-float, softfp-float, and hard-float builds:

  * ``libble_controller_s112_nrf52_0.1.0-1.prealpha.a``
  * ``libble_controller_s132_nrf52_0.1.0-1.prealpha.a``
  * ``libble_controller_s140_nrf52_0.1.0-1.prealpha.a``
