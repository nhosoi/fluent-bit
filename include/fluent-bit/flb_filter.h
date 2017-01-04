/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015-2017 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_FILTER_H
#define FLB_FILTER_H

struct flb_filter_instance;

struct flb_filter_plugin {
    char *name;
    char *description;

    int (*cb_init) (struct flb_filter_instance *, struct flb_config, void *);
    int (*cb_filter) (void *, size_t, char *, int, struct flb_filter_instance,
                      void *, struct flb_config *);
    int (*cb_exit) (void *, struct flb_config *);
};

struct flb_filter_instance {
    int id;                        /* instance id              */
    char name[16];                 /* numbered name            */
    char *match;                   /* match rule based on Tags */
    struct flb_filter_plugin *p;   /* original plugin          */
    struct mk_list properties;
    struct mk_list _head;          /* link to config->filters  */
};

int flb_filter_set_property(struct flb_filter_instance *filter, char *k, char *v);

#endif