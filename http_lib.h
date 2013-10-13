/*
 *  Http put/get/post mini lib
 *  written by L. Demailly
 *  (c) 2013 Anibal Limon - limon.anibal@gmail.com
 *  (c) 1998 Laurent Demailly - http://www.demailly.com/~dl/
 *  (c) 1996 Observatoire de Paris - Meudon - France
 *  see LICENSE for terms, conditions and DISCLAIMER OF ALL WARRANTIES
 *
 * $Id: http_lib.h,v 1.4 1998/09/23 06:14:15 dl Exp $
 *
 */

 /* declarations */
typedef int (*http_base64_encoder)(const char *in, char **out);

/* custom function to read buffer eof */
typedef void (*http_buffer_eof_reader)(int fd);

/* return type */
typedef enum {

  /* Client side errors */
  ERRHOST=-1, /* No such host */
  ERRSOCK=-2, /* Can't create socket */
  ERRCONN=-3, /* Can't connect to host */
  ERRWRHD=-4, /* Write error on socket while writing header */
  ERRWRDT=-5, /* Write error on socket while writing data */
  ERRRDHD=-6, /* Read error on socket while reading result */
  ERRPAHD=-7, /* Invalid answer from data server */
  ERRNULL=-8, /* Null data pointer */
  ERRNOLG=-9, /* No/Bad length in header */
  ERRMEM=-10, /* Can't allocate memory */
  ERRRDDT=-11,/* Read error while reading data */
  ERRURLH=-12,/* Invalid url - must start with 'http://' */
  ERRURLP=-13,/* Invalid port in url */
  

  /* Return code by the server */
  ERR400=400, /* Invalid query */
  ERR403=403, /* Forbidden */
  ERR408=408, /* Request timeout */
  ERR500=500, /* Server error */
  ERR501=501, /* Not implemented */
  ERR503=503, /* Service overloaded */

  /* Succesful results */
  OK0 = 0,   /* successfull parse */
  OK201=201, /* Ressource succesfully created */
  OK200=200  /* Ressource succesfully read */

} http_retcode;

/* CTX */
typedef struct _http_ctx {
	char *server;
	int port;
	char *proxy_server;
	int proxy_port;

	http_base64_encoder b64_enc;
	char *b64_auth;

	http_buffer_eof_reader reader;
} http_ctx;

/* Functions */
extern http_retcode http_parse_url(char *url, char **pfilename);
extern http_retcode http_proxy_url(char *url);
extern http_retcode http_put(char *filename, char *data, int length, 
			int overwrite, char *type);
extern http_retcode http_get(char *filename, char **pdata,int *plength,
			char *typebuf);
extern http_retcode http_delete(char *filename);
extern http_retcode http_head(char *filename, int *plength, char *typebuf);
extern http_retcode http_post(char *filename, char *data, int length,
			char *type, char **pdata, int *plength, char **ptype);
extern void http_set_base64_encoder(http_base64_encoder enc);
extern http_retcode http_set_basic_auth(char *user, char *pass);
extern void http_set_buffer_eof_reader(http_buffer_eof_reader reader);

/* Multi-thread functions */
extern http_retcode httpmt_parse_url(http_ctx *ctx, char *url, char **pfilename);
extern http_retcode httpmt_proxy_url(http_ctx *ctx, char *url);
extern http_retcode httpmt_put(http_ctx *ctx, char *filename, char *data, int length, 
		int overwrite, char *type);
extern http_retcode httpmt_get(http_ctx *ctx, char *filename, char **pdata,
		int *plength, char *typebuf);
extern http_retcode httpmt_delete(http_ctx *ctx, char *filename);
extern http_retcode httpmt_head(http_ctx *ctx, char *filename, int *plength,
		char *typebuf);
extern http_retcode httpmt_post(http_ctx *ctx, char *filename, char *data, int length,
		char *type, char **pdata, int *plength, char **ptype);
extern void httpmt_set_base64_encoder(http_ctx *ctx, http_base64_encoder enc);
extern http_retcode httpmt_set_basic_auth(http_ctx *ctx, char *user, char *pass);
extern void httpmt_set_buffer_eof_reader(http_ctx *ctx, http_buffer_eof_reader reader);
