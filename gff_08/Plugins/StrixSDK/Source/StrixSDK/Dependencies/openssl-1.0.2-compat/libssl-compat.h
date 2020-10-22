#pragma once

#if OPENSSL_VERSION_NUMBER < 0x10100000L

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <stdint.h>

#undef SSL_CTX_set_options
#undef SSL_is_init_finished
#undef SSL_get_state

#ifdef __cplusplus
extern "C" {
#endif

const SSL_METHOD *TLS_method(void);

int OPENSSL_init_ssl(uint64_t opts, const void *settings);

int OPENSSL_init_crypto(uint64_t opts, const void *settings);

uint32_t SSL_CTX_set_options(SSL_CTX *ctx, uint32_t op);

int SSL_is_init_finished(SSL *ssl);

int SSL_get_state(SSL *ssl);

#ifdef __cplusplus
}
#endif

#endif