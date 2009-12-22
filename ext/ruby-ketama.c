#include "ruby-ketama.h"

static VALUE rb_cKetama;
ketama_continuum cont;

static VALUE initialize(VALUE self, VALUE filename_str) {
  char *filename;
  filename = StringValuePtr(filename_str);
  ketama_roll(&cont, filename);
  return self;
}

static VALUE get_server(VALUE self, VALUE key_str) {
  char *key;
  mcs *server;
  key = StringValuePtr(key_str);
  server = ketama_get_server(key, cont);
  return rb_str_new2(server->ip);
}

void Init_ketama() {
  VALUE rb_cKetama = rb_define_class("Ketama", rb_cObject);
  rb_define_method(rb_cKetama, "initialize", initialize, 1);
  rb_define_method(rb_cKetama, "server", get_server, 1);
}