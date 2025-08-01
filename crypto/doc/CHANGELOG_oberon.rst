.. _crypto_changelog_oberon:

Changelog - nrf_oberon
######################

.. contents::
   :local:
   :depth: 2

All notable changes to this project are documented in this file.

nrf_oberon - 3.0.17
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Add support for XMSS verify and XMSS^MT verify (PQC signature algorithms).
  Based on [NIST SP 800-208](https://csrc.nist.gov/pubs/sp/800/208/final).
  With support for SHA256 and SHAKE256 hashing.
* Add support for ML-KEM (aka Kyber, PQC key encapsulation mechanism).
  Based on [FIPS - Module-Lattice-Based Key-Encapsulation Mechanism Standard](https://csrc.nist.gov/pubs/fips/203/final).
  With support for security levels ML-KEM-512, ML-KEM-768, ML-KEM-1024.
* Add support for ML-DSA (aka Dilithium, PQC digital signature algorithm).
  Based on [FIPS - Module-Lattice-Based Digital Signature Standard](https://csrc.nist.gov/pubs/fips/204/final).
  With support for security levels ML-DSA-44, ML-DSA-65, ML-DSA-87.

Library built against Mbed TLS version 3.6.4.

Added the following Oberon crypto libraries for nRF91, nRF53, nRF52, and nRF51 Series.

.. note::
   The *short-wchar* libraries are compiled with a wchar_t size of 16 bits.

* nrf_oberon, nRF91 and nRF53 Series application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.17.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.17.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.17.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.17.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.17.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.17.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.17.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.17.lib``

* nrf_oberon, nRF53 Series network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.17.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.17.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.17.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.17.lib``

* nrf_oberon, nRF52 Series variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.17.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.17.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.17.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.17.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.17.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.17.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.17.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.17.lib``

* nrf_oberon, nRF51 Series variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.17.a`
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.17.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.17.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.17.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.17.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.17.lib``

nrf_oberon - 3.0.16
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Added support for LMS verify and HSS verify (PQC signature algorithms).
  This is based on NIST SP 800-208 with support for SHA256 and SHAKE256 hashing.
* Added AES key wrap algorithms with and without padding based on NIST standard Methods for Key Wrapping.
* Added support for XChaCha20 and XChaCha20-Poly1305.
  This is based on XChaCha.
* Added support for secp256k1 (Koblitz curves).
  This is based on NIST SP 800-56A Rev. 3 and FIPS 186-5.
* Added AES key wrap algorithms with and without padding based on NIST standard Methods for Key Wrapping.
* Added experimental support for WPA3-SAE/WPA3-SAE-H2E based on IEEE standard P802.11-REVme/D7.0, Part 11.
* Added experimental support for Ascon-Hash256 (fixed size, XOF, CXOF) and Ascon-AEAD128. 
  This is based on NIST SP 800-232.

Library built against Mbed TLS version 3.6.2.

Added the following Oberon crypto libraries for nRF91, nRF53, nRF52, and nRF51 Series.

.. note::
   The *short-wchar* libraries are compiled with a wchar_t size of 16 bits.

* nrf_oberon, nRF91 and nRF53 Series application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.16.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.16.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.16.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.16.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.16.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.16.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.16.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.16.lib``

* nrf_oberon, nRF53 Series network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.16.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.16.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.16.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.16.lib``

* nrf_oberon, nRF52 Series variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.16.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.16.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.16.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.16.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.16.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.16.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.16.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.16.lib``

* nrf_oberon, nRF51 Series variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.16.a`
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.16.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.16.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.16.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.16.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.16.lib``

nrf_oberon - 3.0.15
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Added missing ocrypto functions for SECP160 curves that broke some configurations.
* Fixed a bug that caused AEAD encryption/decryption with AES-CCM to produce incorrect results for large buffers (>1MB data with 12 byte nonce).

Library built against Mbed TLS version 3.5.2.

Added the following Oberon crypto libraries for nRF91, nRF53, nRF52, and nRF51 Series.

.. note::
   The *short-wchar* libraries are compiled with a wchar_t size of 16 bits.

* nrf_oberon, nRF91 and nRF53 Series application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.15.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.15.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.15.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.15.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.15.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.15.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.15.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.15.lib``

* nrf_oberon, nRF53 Series network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.15.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.15.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.15.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.15.lib``

* nrf_oberon, nRF52 Series variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.15.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.15.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.15.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.15.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.15.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.15.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.15.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.15.lib``

* nrf_oberon, nRF51 Series variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.15.a`
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.15.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.15.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.15.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.15.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.15.lib``

nrf_oberon - 3.0.14
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Added ECDH key check functions for P521 (secp521r1).
* Added SHA-3 family of cryptographic hash functions
  - SHA-3 for hash sizes: 224, 256, 384, 512 (FIPS-PUB-202).
  - SHAKE128, SHAKE256 (FIPS-PUB-202).
  - cSHAKE128, cSHAKE256 (NIST SP 800-185).
* Added KMAC cryptographic MAC functions based on SHA-3 and cSHAKE
  - KMAC128, KMAC256 (NIST SP 800-185).
* Added Twisted Edwards curve Ed448, Ed448ph (EdDSA).
* Added Montgomery curve X448 (ECDH).
* Added P-521, also known as secp521r1 (ECDSA and ECDH).

Library built against Mbed TLS version 3.5.2.

Added the following Oberon crypto libraries for nRF91, nRF53, nRF52, and nRF51 Series.

.. note::
   The *short-wchar* libraries are compiled with a wchar_t size of 16 bits.

* nrf_oberon, nRF91 and nRF53 Series application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.14.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.14.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.14.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.14.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.14.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.14.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.14.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.14.lib``

* nrf_oberon, nRF53 Series network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.14.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.14.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.14.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.14.lib``

* nrf_oberon, nRF52 Series variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.14.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.14.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.14.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.14.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.14.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.14.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.14.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.14.lib``

* nrf_oberon, nRF51 Series variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.14.a`
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.14.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.14.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.14.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.14.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.14.lib``

nrf_oberon - 3.0.13
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Added Oberon PSA core, a heavily code-size optimized and efficient implementation of PSA core licensed for use on Nordic Semiconductor devices.
* Added ocrypto APIs for PBKDF2 support (CMAC and HMAC using SHA-1, SHA-256).
* Added ocrypto APIs for SPAKE2+ using ECC curve type secp256r1.
* Added Oberon PSA crypto drivers as source distribution with extensive support:
  - AEAD (AES CCM, AES GCM, ChaCha20/Poly1305)
  - Cipher (Chacha20, AES CTR, AES CBC, AES CCM* and AES ECB)
  - EC J-PAKE using ECC curve type secp256r1
  - ECDH using ECC curve types secp224r1, secp256r1, secp384r1
  - X25519
  - ECDSA using ECC curve types secp224r1, secp256r1, secp384r1
  - Ed25519
  - HASH (SHA-1, SHA-224, SHA-256, SHA-384 and SHA-512)
  - HKDF
  - PBKDF2 using CMAC and AES-128
  - PBKDF2 using HMAC and SHA-1 or SHA-256
  - TLS 1.2 PRF functions
  - HMAC, CMAC and CBC MAC
  - RSA PKCS#1 1.5 and 2.1
* Added custom Oberon PSA crypto drivers as source distribution:
  - CTR_DRBG
  - HMAC_DRBG
  - SPAKE2+ using ECC curve type secp256r1
  - SRP

Removed
=======

* Removed binary distribution of Oberon PSA crypto drivers.

Library built against Mbed TLS version 3.3.0.

Added the following Oberon crypto libraries for nRF91, nRF53, nRF52, and nRF51 Series.

.. note::
   The *short-wchar* libraries are compiled with a wchar_t size of 16 bits.

* nrf_oberon, nRF91 and nRF53 Series application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.13.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.13.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.13.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.13.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.13.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.13.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.13.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.13.lib``

* nrf_oberon, nRF53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.13.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.13.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.13.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.13.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.13.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.13.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.13.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.13.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.13.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.13.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.13.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.13.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.13.a`
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.13.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.13.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.13.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.13.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.13.lib``

nrf_oberon - 3.0.12
*******************

New version of the nrf_oberon library with the following changes:

* Incremental ocrypto HMAC API.
* Reduced SHA-1 stack size.
* Improved ECDSA performance.
* Changed the API for PSA Cipher for nrf_oberon PSA Crypto driver (now includes ``iv`` and ``iv_length`` parameters).

The library is built against Mbed TLS version 3.1.0.

Added
=====

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.12.a`
  * :file:`cortex-m33/hard-float/liboberon_psa_3.0.12.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.12.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.12.a`
  * :file:`cortex-m33/soft-float/liboberon_psa_3.0.12.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.12.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.12.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.12.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.12.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.12.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.12.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_psa_3.0.12.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.12.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.12.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.12.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.12.a`
  * :file:`cortex-m4/hard-float/liboberon_psa_3.0.12.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.12.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.12.a`
  * :file:`cortex-m4/soft-float/liboberon_psa_3.0.12.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.12.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.12.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.12.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.12.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.12.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.12.a`
  * :file:`cortex-m0/soft-float/oberon_psa_3.0.12.lib``
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.12.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.12.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_psa_3.0.12.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.12.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.12.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_psa_3.0.12.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.12.lib``


nrf_oberon - 3.0.11
*******************

New version of the nrf_oberon library with the following changes.

Added
=====

* Support for in-place encryption in PSA Crypto, needed for TLS/DTLS.
* PKCS#7 padding for CBC.
* Support for 16 bytes IV for GCM in PSA Crypto APIs.


The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.11.a`
  * :file:`cortex-m33/hard-float/liboberon_psa_3.0.11.a`
  * :file:`cortex-m33/hard-float/liboberon_mbedtls_3.0.11.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.11.a`
  * :file:`cortex-m33/soft-float/liboberon_psa_3.0.11.a`
  * :file:`cortex-m33/soft-float/liboberon_mbedtls_3.0.11.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m33/hard-float/short-wchar/liboberon_mbedtls_3.0.11.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_mbedtls_3.0.11.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m33/hard-float/short-wchar/oberon_mbedtls_3.0.11.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.11.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.11.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_psa_3.0.11.a`
  * :file:`cortex-m33+nodsp/soft-float/liboberon_mbedtls_3.0.11.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_mbedtls_3.0.11.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_mbedtls_3.0.11.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.11.a`
  * :file:`cortex-m4/hard-float/liboberon_psa_3.0.11.a`
  * :file:`cortex-m4/hard-float/liboberon_mbedtls_3.0.11.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.11.a`
  * :file:`cortex-m4/soft-float/liboberon_psa_3.0.11.a`
  * :file:`cortex-m4/soft-float/liboberon_mbedtls_3.0.11.a.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m4/hard-float/short-wchar/liboberon_mbedtls_3.0.11.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_mbedtls_3.0.11.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m4/soft-float/short-wchar/oberon_mbedtls_3.0.11.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_mbedtls_3.0.11.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.11.a`
  * :file:`cortex-m0/soft-float/oberon_psa_3.0.11.lib``
  * :file:`cortex-m0/soft-float/liboberon_mbedtls_3.0.11.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.11.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_psa_3.0.11.a`
    * :file:`cortex-m0/soft-float/short-wchar/liboberon_mbedtls_3.0.11.a`


  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.11.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_psa_3.0.11.lib``
    * :file:`cortex-m0/soft-float/short-wchar/oberon_mbedtls_3.0.11.lib``


nrf_oberon - 3.0.10
*******************

New version of the nrf_oberon library with the following changes:

* Fixed an issue with the ChaChaPoly PSA APIs where more IV sizes than supported by the APIs were accepted.
* Support for the PSA APIs.

Added
=====

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.10.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.10.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.10.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.10.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.10.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.10.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.10.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.10.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.10.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.10.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.10.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.10.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.10.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.10.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.10.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.10.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.10.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.10.lib``

nrf_oberon - 3.0.9
******************

New version of the nrf_oberon library with the following changes.

Added
=====

* PSA API support.

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160, and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.9.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.9.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.9.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.9.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.9.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.9.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.9.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.9.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.9.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.9.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.9.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.9.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.9.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.9.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.9.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.9.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.9.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.9.lib``


nrf_oberon - 3.0.8
******************

New version of the nrf_oberon library with the following changes.

Added
=====

* APIs for doing ECDH calculation using secp256r1 in incremental steps.
* ``ocrypto_`` APIs for SHA-224 and SHA-384.
* ``ocrypto_`` APIs for pbkdf2 for SHA-1 and SHA-256.

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures.

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.8.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.8.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.8.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.8.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.8.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.8.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.8.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.8.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.8.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.8.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.8.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.8.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.8.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.8.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.8.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.8.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.8.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.8.lib``

nrf_oberon - 3.0.7
******************

New version of the nrf_oberon library with the following changes.

Added
=====

The following header files with ocrypto APIs:

* :file:`include/ocrypto_ecdh_p224.h`
* :file:`include/ocrypto_ecdsa_p224.h`

The following header files with Mbed TLS alternate APIs:

* :file:`include/mbedtls/chacha20_alt.h`
* :file:`include/mbedtls/poly1305_alt.h`

The following library-internal symbols for Mbed TLS alternate APIs:

* ECDSA generate key, sign, and verify (secp224r1, secp256r1, curve25519)
* ECDH generate key, compute shared secret (secp224r1, secp256r1, curve25519)

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   The *short-wchar* libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.7.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.7.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.7.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.7.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.7.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.7.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.7.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.7.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.7.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.7.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.7.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.7.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.7.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.7.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.7.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.7.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.7.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.7.lib``

nrf_oberon - 3.0.5
******************

Added
=====

The following header files with ocrypto APIs:

* :file:`include/ocrypto_aes_cbc.h`
* :file:`include/ocrypto_aes_ccm.h`
* :file:`include/ocrypto_aes_cmac.h`
* :file:`include/ocrypto_ecjpake_p256.h`
* :file:`include/ocrypto_hkdf_sha1.h`
* :file:`include/ocrypto_hmac_sha1.h`

The following header files with Mbed TLS alternate APIs:

* :file:`include/mbedtls/ecjpake_alt.h`
* :file:`include/mbedtls/sha1_alt.h`
* :file:`include/mbedtls/sha256_alt.h`

The following library-internal symbols for Mbed TLS alternate APIs:

* ECDSA generate key, sign, and verify (secp256r1)
* ECDH generate key, compute shared secret (secp256r1)

The following Oberon crypto libraries for nRF9160, nRF53, nRF52, and nRF51 architectures:

.. note::
   short-wchar: Those libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nRF9160 and nRF53 application core variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.5.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.5.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.5.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.5.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.5.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.5.lib``

* nrf_oberon, nrf53 network core variants

  * :file:`cortex-m33+nodsp/soft-float/liboberon_3.0.5.a`

  * short-wchar

    * :file:`cortex-m33+nodsp/soft-float/short-wchar/liboberon_3.0.5.a`

  * Keil

    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.5.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.5.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.5.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.5.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.5.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.5.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.5.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.5.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.5.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.5.lib``

nrf_oberon - 3.0.3
******************

Added
=====

* Oberon :file:`ocrypto_poly1305.h` and :file:`ocrypto_sc_p256.h headers`.

The following Oberon crypto libraries for nRF9160, nRF52, and nRF51 architectures:

.. note::
   short-wchar: Those libraries are compiled with a ``wchar_t`` size of 16 bits.


* nrf_oberon, nRF9160 variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.3.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.3.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.3.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.3.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.3.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.3.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.3.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.3.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.3.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.3.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.3.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.3.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.3.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.3.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.3.lib``


Removed
=======

* All 3.0.2 versions of the library and old include files.


nrf_oberon - 3.0.2
******************

Added
=====

* Oberon SRP, Secure Remote Password, :c:func:`ocrypto_srp` functions.

The following Oberon crypto libraries for nRF9160, nRF52, and nRF51 architectures:

.. note::
   short-wchar: Those libraries are compiled with a ``wchar_t`` size of 16 bits.


* nrf_oberon, nRF9160 variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.2.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.2.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.2.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.2.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.2.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.2.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.2.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.2.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.2.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.2.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.2.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.2.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.2.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.2.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.2.lib``


Removed
=======

* All 3.0.0 versions of the library and old include files.

nrf_oberon - 3.0.0
******************

Added
=====

The following Oberon crypto libraries for nRF9160, nRF52, and nRF51 architectures:

.. note::
   The include files and APIs have changed the prefix from ``occ_`` to ``ocrypto_``.

.. note::
   short-wchar: Those libraries are compiled with a ``wchar_t`` size of 16 bits.


* nrf_oberon, nRF9160 variants

  * :file:`cortex-m33/hard-float/liboberon_3.0.0.a`
  * :file:`cortex-m33/soft-float/liboberon_3.0.0.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_3.0.0.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_3.0.0.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_3.0.0.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_3.0.0.lib``

* nrf_oberon, nRF52 variants

  * :file:`cortex-m4/hard-float/liboberon_3.0.0.a`
  * :file:`cortex-m4/soft-float/liboberon_3.0.0.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_3.0.0.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_3.0.0.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_3.0.0.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_3.0.0.lib``

* nrf_oberon, nRF51 variants

  * :file:`cortex-m0/soft-float/liboberon_3.0.0.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_3.0.0.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_3.0.0.lib``


Removed
=======

* All 2.0.7 versions of the library and old include files.


nrf_oberon - 2.0.7
******************

Initial release.

Added
=====

The following Oberon crypto libraries for nRF9160, nRF52, and nRF51 architectures:

.. note::
   short-wchar: Those libraries are compiled with a ``wchar_t`` size of 16 bits.

* nrf_oberon, nrf9160 variants

  * :file:`cortex-m33/hard-float/liboberon_2.0.7.a`
  * :file:`cortex-m33/soft-float/liboberon_2.0.7.a`

  * short-wchar

    * :file:`cortex-m33/hard-float/short-wchar/liboberon_2.0.7.a`
    * :file:`cortex-m33/soft-float/short-wchar/liboberon_2.0.7.a`

  * Keil

    * :file:`cortex-m33/hard-float/short-wchar/oberon_2.0.7.lib``
    * :file:`cortex-m33/soft-float/short-wchar/oberon_2.0.7.lib``

* nrf_oberon, nrf52 variants

  * :file:`cortex-m4/hard-float/liboberon_2.0.7.a`
  * :file:`cortex-m4/soft-float/liboberon_2.0.7.a`

  * short-wchar

    * :file:`cortex-m4/hard-float/short-wchar/liboberon_2.0.7.a`
    * :file:`cortex-m4/soft-float/short-wchar/liboberon_2.0.7.a`

  * Keil

    * :file:`cortex-m4/soft-float/short-wchar/oberon_2.0.7.lib``
    * :file:`cortex-m4/hard-float/short-wchar/oberon_2.0.7.lib``

* nrf_oberon, nrf51 variants

  * :file:`cortex-m0/soft-float/liboberon_2.0.7.a`

  * short-wchar

    * :file:`cortex-m0/soft-float/short-wchar/liboberon_2.0.7.a`

  * Keil

    * :file:`cortex-m0/soft-float/short-wchar/oberon_2.0.7.lib``
