/*
 * Baseband Evaluation
 *
 * Functional and speed test for various baseband functions.
 *
 * Copyright (C) 2018 by Christian Zuckschwerdt <zany@triq.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "r_util.h"

void assert_equal(const char *got, const char *want);

void assert_equal(const char *got, const char *want) {
    if (strcmp(got, want) == 0) {
        return;
    }

    printf("Error: mismatching strings!\n");
    printf("(- = want, + = got)\n");
    printf("- %s\n", want);
    printf("+ %s\n", got);
    exit(1);
}

int main(void)
{
    char *url = "https://foo.bar/foz/baz?p=pass&u=user";
    char *scrubbed = scrub_password_from_url(url, "########");
    assert_equal(scrubbed, "https://foo.bar/foz/baz?p=########&u=user");

    url = "https://foo.bar/foz/baz?u=user&p=pass";
    scrubbed = scrub_password_from_url(url, "++");
    assert_equal(scrubbed, "https://foo.bar/foz/baz?u=user&p=++");

    url = "https://foo.bar/foz/baz?u=user";
    scrubbed = scrub_password_from_url(url, "foobar");
    assert_equal(scrubbed, "https://foo.bar/foz/baz?u=user");
}
