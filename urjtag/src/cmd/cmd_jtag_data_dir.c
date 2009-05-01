/*
 * Copyright 2008 Mike Frysinger
 * Copyright 2008 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <config.h>
#include <urjtag/jtag.h>

static const char *jtag_argv0;

void
urj_cmd_jtag_set_argv0(const char *argv0)
{
    jtag_argv0 = argv0;
}

#ifdef JTAG_RELOCATABLE

#include <stdlib.h>
#include <string.h>

extern char *make_relative_prefix (const char *progname,
                                   const char *bin_prefix,
                                   const char *prefix);

static char *jtag_data_dir = NULL;

const char *
urj_cmd_jtag_get_data_dir (void)
{
    if (jtag_data_dir)
        return jtag_data_dir;

    jtag_data_dir =
        make_relative_prefix (jtag_argv0, JTAG_BIN_DIR, JTAG_DATA_DIR);
    if (!jtag_data_dir)
        jtag_data_dir = JTAG_DATA_DIR;

    return jtag_data_dir;
}

#else

const char *
urj_cmd_jtag_get_data_dir (void)
{
    return JTAG_DATA_DIR;
}

#endif