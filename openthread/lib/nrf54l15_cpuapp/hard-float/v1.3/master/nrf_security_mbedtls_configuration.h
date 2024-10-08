/*
 * Copyright (c) 2021 Nordic Semiconductor
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 *
 */

#ifndef MBEDTLS_CONFIG_PSA_H
#define MBEDTLS_CONFIG_PSA_H

#if defined(MBEDTLS_PSA_CRYPTO_CONFIG_FILE)
#include MBEDTLS_PSA_CRYPTO_CONFIG_FILE
#else
#error "MBEDTLS_PSA_CRYPTO_CONFIG_FILE expected to be set"
#endif


#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************/
/* Require built-in implementations based on CRACEN PSA requirements
 *
 * NOTE: Required by the CRACEN driver still, which is checking for
 * MBEDTLS crypto definitions.
 */
/****************************************************************/
#if defined(CONFIG_PSA_NEED_CRACEN_KEY_MANAGEMENT_DRIVER)
#define MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS
#endif

/****************************************************************/
/* Require built-in implementations based on PSA requirements
 *
 * NOTE: Required by the TLS stack still, which is checking for MBEDTLS crypto definitions.
 */
/****************************************************************/

/* Required for MBEDTLS_HAS_ECDH_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_ECDH)
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECP_C
#define MBEDTLS_BIGNUM_C
#endif

/* Required for MBEDTLS_HAS_ECDSA_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_ECDSA)
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#endif

/* Required for MBEDTLS_HAS_RSA_CIPHERSUITE_REQUIREMENTS
 *
 * The requirements should all be met on MBEDTLS configurations already.
 */

#if defined(PSA_WANT_ALG_SHA_1)
/* TLS/DTLS 1.2 requires SHA-1 support using legacy API for now.
 * Revert this when resolving NCSDK-20975.
 */
#if defined(CONFIG_MBEDTLS_TLS_LIBRARY)
#define MBEDTLS_SHA1_C
#endif
#endif

/* Required for MBEDTLS_HAS_ECJPAKE_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_SHA_256)
#define MBEDTLS_SHA224_C
#define MBEDTLS_SHA256_C
#endif

/* Required for MBEDTLS_HAS_CBC_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_CBC_PKCS7)
/* NB: check_config does not do any checks for CBC. */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_AES_C
#endif

/* Required for MBEDTLS_HAS_CCM_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_CCM)
#define MBEDTLS_CCM_C
#define MBEDTLS_AES_C
#endif

/* Required for MBEDTLS_HAS_GCM_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_GCM)
#define MBEDTLS_GCM_C
#define MBEDTLS_AES_C
#endif

/* Required for MBEDTLS_HAS_CHACHAPOLY_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_CHACHA20_POLY1305)
#if defined(PSA_WANT_KEY_TYPE_CHACHA20)
#define MBEDTLS_CHACHA20_C
#define MBEDTLS_POLY1305_C
#define MBEDTLS_CHACHAPOLY_C
#endif
#endif

/* Because we have enabled MBEDTLS_ECP_C we need atleast one ECC curve type. */
#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_256)
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_384)
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_BRAINPOOL_P_R1_512)
#define MBEDTLS_ECP_DP_BP512R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_MONTGOMERY_255)
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#endif

#if defined(PSA_WANT_ECC_MONTGOMERY_448)
#define MBEDTLS_ECP_DP_CURVE448_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_R1_192)
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_R1_224)
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_R1_256)
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_R1_384)
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_R1_521)
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_K1_192)
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_K1_224)
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#endif

#if defined(PSA_WANT_ECC_SECP_K1_256)
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#endif

/* Required for MBEDTLS_HAS_ECJPAKE_CIPHERSUITE_REQUIREMENTS */
#if defined(PSA_WANT_ALG_JPAKE)
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ECJPAKE_C
#endif

/* Nordic added */
#if defined(MBEDTLS_PK_PARSE_C)
#define MBEDTLS_ASN1_PARSE_C
#endif

#if defined(MBEDTLS_PK_WRITE_C)
#define MBEDTLS_ASN1_WRITE_C
#endif

/* TLS/DTLS additions */
#if !defined(MBEDTLS_PSA_CRYPTO_SPM)
/* #undef MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */
/* #undef MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED */
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
/* #undef MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED */
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
/* #undef MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */
/* #undef MBEDTLS_KEY_EXCHANGE_RSA_ENABLED */
/* #undef MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED */
/* #undef MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */

#if     defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)    || \
	defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)     || \
	defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)   || \
	defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)      || \
	defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)           || \
	defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)       || \
	defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)           || \
	defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)       || \
	defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PK_C
#define MBEDTLS_OID_C
#define MBEDTLS_DHM_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_PEM_PARSE_C
#endif

#endif /* MBEDTLS_PSA_CRYPTO_SPM */

#if defined(CONFIG_MBEDTLS_DEBUG)
#define MBEDTLS_ERROR_C
#define MBEDTLS_DEBUG_C
#define MBEDTLS_SSL_DEBUG_ALL
#endif

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CONFIG_PSA_H */
