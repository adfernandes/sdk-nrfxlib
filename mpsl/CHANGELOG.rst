.. _mpsl_changelog:

Changelog
#########

.. contents::
   :local:
   :depth: 2


All the notable changes to this project are documented on this page.

Main branch
***********

Changes
=======

* The functions :c:func:`mpsl_hwres_dppi_channel_alloc` and :c:func:`mpsl_hwres_ppib_channel_alloc` added by the :file:`mpsl_hwres.h` file need to be implemented by MPSL users. (KRKNWK-15977)
* For the nRF54L Series devices, the inter-domain PPIB connections for Front-End Modules are configured internally in the MPSL.
  You no longer need to configure the PPIB connections.
  The field ``ppib_channels`` of the :c:struct:`mpsl_fem_gpiote_pin_config_t` structure is removed. (KRKNWK-15977)
* Added the ``phy`` parameter to the function :c:func:`mpsl_fem_tx_power_split` and to the function type :c:type:`mpsl_fem_power_model_output_fetch_t`. (KRKNWK-20435)

Added
=====

* Added the :file:`mpsl_hwres.h` file, which defines an API for hardware resources allocation. (KRKNWK-15977)
* Added support for the nRF21540 Front-End Module in GPIO/SPI mode on the nRF54L Series SoCs. (KRKNWK-15977)
* Added support for the Simple GPIO Front-End Module on the nRF54L Series SoCs. (KRKNWK-20506)
* Added support for boosting the current timeslot priority for the nRF 802.15.4 Radio Driver. (KRKNWK-19125)

Bug fixes
=========

* Fixed a rare issue where radio events would be dropped if high-frequency crystal tuning was needed due to a large temperature change when starting the HFXO.
  In the worst-case scenario, MPSL would not recover from this state and continue to drop radio events.
  This issue applies only to the nRF54L Series devices. (DRGN-25261)

Removed
=======

* Removed the deprecated function :c:func:`mpsl_fem_simple_gpio_interface_config_get`.

nRF Connect SDK v3.0.0
**********************

Changes
=======

* Documented that the :c:func:`mpsl_clock_task_trigger_on_rtc_start_set` function is supported only on the nRF52 and nRF53 Series.
* Added support for the nRF21540 GPIO Front-End Module on the nRF54L Series SoCs. (KRKNWK-19928)
* The activation of the nRF2220 Front-End Module CS pin now requires a call to the :c:func:`mpsl_fem_enable` function. (KRKNWK-19588)
* Applied Errata 22 and Errata 24 to the Front-End Modules on the nRF54L15 SoC. (KRKNWK-19588)
* The activation of the nRF21540 Front-End Module PDN pin (in both GPIO and GPIO+SPI modes) now requires a call to the :c:func:`mpsl_fem_enable` function.
  The ``PA time gap`` configuration parameter of the nRF21540 Front-End Module can now have greater values, that allow to activate the ``TX_EN`` pin earlier during the ramp-up of the RADIO.
  The nRF21540 Front-End Module now requires fewer resources (PPI/DPPI channels, EGU channels).
  For the nRF21540 Front-End Module, only one compare channel of a TIMER is required to configure PA or LNA activation for the :c:enumerator:`MPSL_FEM_EVENT_TYPE_TIMER` event type.
* The callback passed to the :c:func:`mpsl_clock_hfclk_request` function will be executed when the HFCLK has started and is stable (EVENT_XOTUNED has occurred). (KRKNWK-19689)

Added
=====

* Added the functions :c:func:`mpsl_clock_ctrl_source_register` and :c:func:`mpsl_clock_ctrl_source_unregister` to provide :ref:`Experimental <nrf:software_maturity>` support for running MPSL with an external clock driver.
  The APIs are only supported on nR54H Series SoCs.
  Using these functions makes it possible to use an external clock driver, such as one provided by the |NCS|.
  This fixes an issue on nRF54H Series where MPSL would assert or get suboptimal performance when other application components attempt to use a clock. (DRGN-21843)
* On the nRF54L15 SoC, Errata 39 is now applied.
* Added the defines :c:macro:`MPSL_TIMER0` to clarify which timer is being used by MPSL and the timeslot implementation. (DRGN-24434)
* New API provided for integration with an external power management system.
  The API is only supported on nRF54H Series SoCs.
  This API makes it possible to use an external power management system, such as the one provided by the |NCS|, to request low latency mode and to request wakeup in time for a future event.
  Added the functions :c:func:`mpsl_pm_init` and :c:func:`mpsl_pm_uninit` to enable and disable integration.
  Added the functions :c:func:`mpsl_pm_params_get`, :c:func:`mpsl_pm_low_latency_requested`, :c:func:`mpsl_pm_low_latency_state_set` and :c:func:`mpsl_pm_low_latency_state_get` to register wakeup time and request low latency. (DRGN-17150)
* Added the functions :c:func:`mpsl_fem_nrf2220_temperature_changed`, :c:func:`mpsl_fem_nrf2220_temperature_changed_update_request`, and :c:func:`mpsl_fem_nrf2220_temperature_changed_update_now` to compensate the temperature of the nRF2220 Front-End Module. (KRKNWK-19862)

Removed
=======

* Removed the deprecated function :c:func:`mpsl_fem_prepare_powerdown`. (KRKNWK-16691)

Bug fixes
=========

* Fixed an issue where the GRTC interrupt could be left pending after :c:func:`mpsl_init` had run.
  In |NCS| this could cause stack corruption early in the Zephyr init sequence after a softreset. (DRGN-24850)
* Fixed an issue where :c:func:`mpsl_constlat_request_callback` would be called more often than :c:func:`mpsl_lowpower_request_callback`. (DRGN-25031)
  This would only occur under rare conditions when two timing events are spaced very close to each other.
  This may cause an assertion if the nrfx power driver is used to implement these callbacks.
  The issue causes the power consumption to increase, and may eventually lead to the assertion.

nRF Connect SDK v2.9.0
**********************

Bug fixes
=========
* Fixed an issue where the functions :c:func:`mpsl_clock_hfclk_request` and :c:func:`mpsl_clock_hfclk_release` could end up not working after :c:func:`mpsl_uninit`
  This could happen if LFRC was used as clock source (DRGN-23325)

nRF Connect SDK v2.8.0
**********************

Changes
=======

* Removed support for running MPSL on the nRF54L15 PDK v0.7.0 and earlier. (DRGN-23325)
* Removed support for running MPSL on the Engineering A revision of the nRF54H20 SoC. (DRGN-23325)
* On nRF54L Series devices, the application now needs to implement :c:func:`mpsl_constlat_request_callback` and :c:func:`mpsl_lowpower_request_callback`.
  This is already added to the MPSL driver in the |NCS|. (DRGN-22562)
* Removed the :file:`mpsl_coex.h` API. (DRGN-22567)
* The timeslot implementation now starts ``TIMER0`` a couple microseconds later.
  It now starts when the ``MPSL_TIMESLOT_SIGNAL_START`` callback is given.

Added
=====

* Added production support for the nRF54L Series. (DRGN-23325)
* Added :c:func:`mpsl_fem_enable` to allow turning on the Front-End Module earlier than through a call to :c:func:`mpsl_fem_pa_configuration_set` (KRKNWK-19275).
  Added implementation of :c:func:`mpsl_fem_enable` for nRF2220 Front-End Module.
* Added the defines :c:macro:`MPSL_PPI_CHANNELS_USED_MASK`, :c:macro:`MPSL_DPPIC_CHANNELS_USED_MASK`, :c:macro:`MPSL_DPPIC10_CHANNELS_USED_MASK`, :c:macro:`MPSL_DPPIC20_CHANNELS_USED_MASK`, and :c:macro:`MPSL_DPPIC020_CHANNELS_USED_MASK`.
  These represent the same resources as ``MPSL_RESERVED_PPI_CHANNELS``, but also specify the DPPI controller the channels belongs to.
* Added the defines :c:macro:`MPSL_PPIB11_CHANNELS_USED_MASK`, :c:macro:`MPSL_PPIB21_CHANNELS_USED_MASK`, and :c:macro:`MPSL_IPCT130_CHANNELS_USED_MASK`.
  These represent the PPIB and IPCT resources used.

nRF Connect SDK v2.7.0
**********************

Changes
=======

* Fixed a rare issue that could cause a scheduler assert if interrupts were disabled for a longer period of time (DRGN-24327).
  Note that disabling interrupts for a longer period of time is not allowed.
* The default bit width within timeslots for ``TIMER0`` has been increased from 24 to 32 bits.
  The user may still configure ``TIMER0`` however they like during the timeslot. (DRGN-19050)
* New FEM protocol APIs are provided to control the PA power, the previous APIs are removed.
  This change does not affect applications developed in the |NCS| context.
  :c:func:`mpsl_fem_pa_power_control_set` replaces :c:func:`mpsl_fem_pa_gain_set`.
  :c:func:`mpsl_fem_caps_get` replaces :c:func:`mpsl_fem_pa_is_configured`.
  The :c:struct:`mpsl_tx_power_split_t` structure contains the new field ``fem_pa_power_control`` to be used with the :c:func:`mpsl_fem_pa_power_control_set` function.
  The :c:type:`mpsl_fem_gain_t` type is deprecated, please use :c:type:`mpsl_fem_pa_power_control_t` type instead (KRKNWK-18729).
* The FEM libraries for nRF2220 and nRF2240 no more link directly to the TWIM library.

  * The TWI implementation now needs to be provided externally.
  * The limitation that only the TWIM0 instance could be used for nRF2220 and nRF2240 devices is removed.
  * :c:struct:`mpsl_fem_twi_if_t` replaces :c:struct:`mpsl_fem_twi_config_t`.
  * The ``twi_if`` field replaces the ``twi_config`` field within :c:struct:`mpsl_fem_nrf2220_interface_config_t` and :c:struct:`mpsl_fem_nrf2240_interface_config_t` (KRKNWK-19010).

nRF Connect SDK v2.6.0
**********************

All the notable changes included in the |NCS| v2.6.0 release are documented in this section.

Changes
=======

* The MPSL radio notification API has been removed. (DRGN-20447)

nRF Connect SDK v2.5.0
**********************

All the notable changes included in the |NCS| v2.5.0 release are documented in this section.

Changes
=======

* FEM-related firmware is now built and deployed into separate libraries, one for each FEM implementation (such as ``simple_gpio``).
* The :c:func:`mpsl_calibration_timer_handle` function must now be called when calibrating.

Added
=====
* Added :c:func:`mpsl_tx_power_dbm_to_radio_register_convert` to convert supported power in dBm to a register code for RADIO. (KRKNWK-17367)
* Added :c:func:`mpsl_clock_task_trigger_on_rtc_start_set` to trigger a PPI/DPPI task when the RTC starts. (DRGN-20396)

nRF Connect SDK v2.4.0
**********************

All the notable changes included in the |NCS| v2.4.0 release are documented in this section.

Changes
=======

* Removed deprecated API for specifying the FEM pin configuration type associated with :c:macro:`MPSL_FEM_PIN_CFG_TYPE_PIN_PORT`.
  Only the :c:struct:`mpsl_fem_pin_t` configuration is supported as a FEM pin configuration now (KRKNWK-16496).

Added
=====
* Function for getting configuration of simple GPIO front-end module :c:func:`mpsl_fem_simple_gpio_interface_config_get`.

nRF Connect SDK v2.3.0
**********************

All the notable changes included in the |NCS| v2.3.0 release are documented in this section.

Added
=====

* The bool parameter ``tx_power_ceiling`` to the external model used by the :c:func:`mpsl_fem_tx_power_split` function.
  When enabled, the function returns the ceiling value instead of the floor.

Bug fixes
=========

* Fixed a rare issue that could cause a scheduler assert if two roles were running (DRGN-18308).
* Fixed a rare issue that could cause an assert when requesting timeslots with type ``MPSL_TIMESLOT_REQ_TYPE_EARLIEST`` (DRGN-18555).

nRF Connect SDK v2.2.0
**********************

All the notable changes included in the |NCS| v2.2.0 release are documented in this section.

Bug fixes
=========

* Fixed an issue where the scheduler could put events in the past (DRGN-17851, DRGN-18105).

nRF Connect SDK v2.1.0
**********************

All the notable changes included in the |NCS| v2.1.0 release are documented in this section.

Added
=====

* Support for the nRF21540 GPIO & SPI front-end module.
  SPI is used to set Tx gain of the nRF21540 in runtime.
  Support for this mode of operation for nRF21540 with Bluetooth LE is experimental.
* Support for adding an optional external model used to split the requested transmit power into components.
  This is then used by :c:func:`mpsl_fem_tx_power_split`. (KRKNWK-14464)
* An experimental version of a built-in nRF21540 GPIO & SPI front-end module compensation model.

Changes
=======

* Removed the :c:func:`nrf_802154_fal_tx_power_get` function that is not used anymore by nRF 802.15.4 Radio Driver. (KRKNWK-14336)
* Changed :c:func:`mpsl_fem_tx_power_split` function so the :c:member:`mpsl_tx_power_split_t.radio_tx_power` field contains a value supported by the RADIO peripheral.
  Previously the value needed to be adjusted before applying to the RADIO peripheral. (KRKNWK-14323)
* Changed :c:struct:`mpsl_fem_gpiote_pin_config_t` and :c:struct:`mpsl_fem_gpio_pin_config_t` to require GPIO port address, port number and relative pin number instead of the absolute pin number. (KRKNWK-11891)
* Added production support for the 1-wire coexistence interface on the Nordic nRF52 Series. (DRGN-16439)
* Added :c:func:`mpsl_clock_hfclk_latency_set` which may be used to communicate the true high-frequency oscillator ramp-up time to MPSL.
  When not used, MPSL will make a worst-case assumption. (DRGN-13559)
* Added :c:func:`mpsl_tx_power_radio_supported_power_adjust` which lets users adjust the TX power to a value supported by the radio peripheral. (KRKNWK-14770)
* Changed :c:func:`mpsl_fem_tx_power_split` so that the returned front-end module gain component is a structure containing the gain in dB and a front-end module implementation specific private setting.
  Changed :c:func:`mpsl_fem_pa_gain_set` to accept this structure and apply the settings that it stores.
* Changed :c:func:`mpsl_fem_tx_power_split` to return the real achieved output power.

nRF Connect SDK v2.0.0
**********************

All the notable changes included in the |NCS| v2.0.0 release are documented in this section.

Added
=====

* Support for changing PA gain during runtime through MODE pin switching for the nRF21540 GPIO front-end module.

Changes
=======

* Removed support for running MPSL on the nRF5340 PDK (DRGN-15174).
* Timeslot API values ``MPSL_TIMESLOT_DISTANCE_MAX_US`` and ``MPSL_TIMESLOT_EARLIEST_TIMEOUT_MAX_US`` increased to 256 seconds (DRGN-16800).
* Extended  :c:struct:`mpsl_fem_nrf21540_gpio_interface_config_t` with :c:member:`mpsl_fem_nrf21540_gpio_interface_config_t.mode_pin_config`
  and :c:member:`mpsl_fem_nrf21540_gpio_interface_config_t.fem_config.pa_gains_db`

Bug fixes
=========

* Fixed an issue where :c:func:`mpsl_uninit` would not disable the PPI channels used by MPSL (DRGN-16515).
* Fixed an issue where :c:func:`mpsl_init` would reject a certain clock configuration for no longer applicable legacy reasons (DRGN-16884).
* Fixed an issue where MPSL could assert when radio notifications on ACTIVE (:c:enumerator:`MPSL_RADIO_NOTIFICATION_TYPE_INT_ON_ACTIVE` or :c:enumerator:`MPSL_RADIO_NOTIFICATION_TYPE_INT_ON_BOTH`) were used (DRGN-16642).
* Fixed an issue where :c:func:`mpsl_uninit` would hang indefinitely when the RC oscillator was used as the Low Frequency Clock source (DRGN-16515).
* Fixed an issue where the High Frequency Clock would stay active if it was turned on between timing events. This could occur during Low Frequency Clock calibration when using the RC oscillator as the Low Frequency Clock source (DRGN-17014).

nRF Connect SDK v1.9.0
**********************

All the notable changes included in the |NCS| v1.9.0 release are documented in this section.

Added
=====

* Added a new header file :file:`mpsl_dppi_protocol_api.h` which exposes DPPI channels that have a fixed configuration during the lifetime of a radio event (DRGN-16308).
  This will facilitate debugging of protocol implementations.
  Currently these channels are guaranteed to be applied correctly for Bluetooth only.

nRF Connect SDK v1.8.0
**********************

All the notable changes included in the |NCS| v1.8.0 release are documented in this section.

Added
=====

* Added support for the Simple GPIO Front-End Module implementation on the nRF53 Series.
* Added support and separate documentation for Bluetooth External Radio Coexistence on the nRF52 Series (DRGN-11849).
* Added experimental support for the 1-wire coexistence interface on the nRF52 Series (DRGN-16439).

Changes
=======

* References to Bluetooth support were moved away from :file:`projects/mpsl/doc/public/doc/cx.rst`.
  Its scope is now limited to IEEE 802.15.4 External Radio Coexistence.

Bug fixes
=========

* Fixed an issue where the current consumption in some cases was high after the end of a timeslot when using ``MPSL_TIMESLOT_HFCLK_CFG_NO_GUARANTEE``.
  Now the time from the request with type ``MPSL_TIMESLOT_REQ_TYPE_EARLIEST`` until the event starts is in some cases increased (DRGN-16506).

nRF Connect SDK v1.7.0
**********************

All the notable changes included in the |NCS| v1.7.0 release are documented in this section.

Added
=====

* Added support for nRF21540 GPIO Front-End Module for nRF53 Series.
* Added a public interface for the radio coexistence protocol API (KRKNWK-7490).
  This public interface can be used to replace the example implementation of the radio coexistence with other implementations compliant with other Packet Traffic Arbitration (PTA) interfaces.

Changes
=======

* The :file:`mpsl_fem_protocol_api.h` was moved from the :file:`include` directory to the :file:`include/protocol` directory (KRKNWK-10507).
* The start signal jitter for the timeslot API (``MPSL_TIMESLOT_START_JITTER_US``) has been reduced to 1us. (DRGN-15842).

nRF Connect SDK v1.6.0
**********************

All the notable changes included in the nRF Connect SDK v1.6.0 release are documented in this section.

Added
=====

* Added an API to set and get a flag that determines whether to apply the DEVICE-CONFIG-254.
  The API user shall set the flag to desired value with :c:func:`mpsl_fem_device_config_254_shall_apply_set`.
  The protocol stacks' responsibility is to check the flag value using :c:func:`mpsl_fem_device_config_254_shall_apply_get` and apply the configuration when the flag value is true.
* Added support for the nRF5340 device, which was previously only supported for evaluation purposes (DRGN-8639).
* Added a function to the FEM protocol API to disable FEM when no radio activity is expected.
  This function is intended to reduce power consumption (KRKNWK-8842).

Changes
=======

* Reserved TIMER1 for use by MPSL on nRF5340 (DRGN-15721).

Bug fixes
=========

* Fixed an issue where the clock configuration option :c:member:`mpsl_clock_lfclk_cfg_t.skip_wait_lfclk_started` did not work as expected with nRF5340 devices (DRGN-15223).

nRF Connect SDK v1.5.0
**********************

All the notable changes included in the nRF Connect SDK v1.5.0 release are documented in this section.

Added
=====

* Added a new signal to the MPSL timeslot: ``MPSL_TIMESLOT_SIGNAL_OVERSTAYED``.
  This signal is given to the application when a timeslot session is closed too late (DRGN-14677).

* Added a new clock configuration option :c:member:`skip_wait_lfclk_started` in :c:struct:`mpsl_clock_lfclk_cfg_t`, which does not wait for the start of the low-frequency clock (DRGN-14204).

* Added macro MPSL_RESERVED_PPI_CHANNELS for a bit mask of (D)PPI channels reserved by MPSL (DRGN-13356).

Bug fixes
=========

* Fixed an issue where the low-frequency clock was configured incorrectly when the source configuration signal was set to either External Full swing or External Low swing (DRGN-15064).

* Fixed an issue where MPSL waited for the low-frequency clock to start even though it was configured not to wait for it (DRGN-15176).

nRF Connect SDK v1.4.0
**********************

All the notable changes included in the nRF Connect SDK v1.4.0 release are documented in this section.

Changes
=======

* Changed the timeslot implementation to support up to 8 concurrent sessions (DRGN-13952).
  It is now necessary to supply a timeslot context configuration using :c:func:`mpsl_timeslot_session_count_set`.
  All timeslot APIs now take a ``session_id`` as input.
  The session id is retrieved from :c:func:`mpsl_timeslot_session_open`.

* Added an API to use Front-End Modules, like the nRF21540 GPIO or a simple GPIO, with the protocols and an API to configure them using the application.
  Only the nRF52 Series is supported.

Bug fixes
=========

* Fixed an issue where both the high-frequency clock and ``TIMER0`` were not turned off during idle periods shorter than 9 ms (DRGN-14152).
  This increased the average power consumption.
  Such a case could occur when running a |BLE| connection with a connection interval of 7.5 ms.

Known Issues and limitations
============================

See the :ref:`nrf:known_issues` page in |NCS| for the list of known issues and limitations for this release.

nRF Connect SDK v1.3.0
**********************

All the notable changes included in the nRF Connect SDK v1.3.0 release are documented in this section.

Added
=====

* Added API for fetching build revision information.
* Added API to set a TX Power envelope.
  Protocols using MPSL will limit their TX power to a value equal to, or lower than, the provided value.
* Added support for using a low-swing and full-swing LF clock.
* The support for integrating an 802.15.4 driver is now improved.

Changes
=======

* Removed ``MPSL_RADIO_NOTIFICATION_DISTANCE_425US`` and replaced it by ``MPSL_RADIO_NOTIFICATION_DISTANCE_420US``.
* On nRF53, the fix for Errata 16 is now applied.
* The scheduling overhead of a timeslot event is reduced.

Bug fixes
=========

* Fixed an issue on nRF53 where an assert could occur when using a timeslot.

nRF Connect SDK v1.2.0
**********************

All the notable changes included in the nRF Connect SDK v1.2.0 release are documented in this section.

Added
=====

* Added a library version with preliminary support for the nRF5340 device.
  The feature set is the same as in the MPSL library for nRF52.
  The following library has been added:

  * :file:`soft-float/libmpsl.a`

Changes
=======

* Removed ``_nrf52`` from the MPSL library file names.
* Version numbers have been removed from the libraries.
* It is no longer allowed to call :c:func:`mpsl_init` if MPSL is already initialized.
* Clock configuration parameters for any stack that uses MPSL must be provided in :c:type:`mpsl_clock_lfclk_cfg_t` to :c:func:`mpsl_init`.
  This now also involves clock accuracy.
* Clock accuracy must be specified in parts per million (ppm).
* Renamed the MPSL clock API for the high-frequency and low-frequency clocks.

MPSL 0.5.0-1.prealpha
*********************

Initial release.

Added
=====

* Added the following MPSL library build variants:

  * ``hard-float/libmpsl_nrf52.a``
  * ``soft-float/libmpsl_nrf52.a``
  * ``softfp-float/libmpsl_nrf52.a``
