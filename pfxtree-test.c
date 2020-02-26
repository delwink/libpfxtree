/*
 *  pfxtree-test - Delwink prefix tree library unit test
 *  Copyright (C) 2017, 2020 Delwink, LLC
 *
 * Redistributions, modified or unmodified, in whole or in part, must retain
 * applicable copyright or other legal privilege notices, these conditions, and
 * the following license terms and disclaimer.  Subject to these conditions,
 * the holder(s) of copyright or other legal privileges, author(s) or
 * assembler(s), and contributors of this work hereby grant to any person who
 * obtains a copy of this work in any form:
 *
 * 1. Permission to reproduce, modify, distribute, publish, sell, sublicense,
 * use, and/or otherwise deal in the licensed material without restriction.
 *
 * 2. A perpetual, worldwide, non-exclusive, royalty-free, irrevocable patent
 * license to reproduce, modify, distribute, publish, sell, use, and/or
 * otherwise deal in the licensed material without restriction, for any and all
 * patents:
 *
 *     a. Held by each such holder of copyright or other legal privilege,
 *     author or assembler, or contributor, necessarily infringed by the
 *     contributions alone or by combination with the work, of that privilege
 *     holder, author or assembler, or contributor.
 *
 *     b. Necessarily infringed by the work at the time that holder of
 *     copyright or other privilege, author or assembler, or contributor made
 *     any contribution to the work.
 *
 * NO WARRANTY OF ANY KIND IS IMPLIED BY, OR SHOULD BE INFERRED FROM, THIS
 * LICENSE OR THE ACT OF DISTRIBUTION UNDER THE TERMS OF THIS LICENSE,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 * A PARTICULAR PURPOSE, AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS,
 * ASSEMBLERS, OR HOLDERS OF COPYRIGHT OR OTHER LEGAL PRIVILEGE BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN ACTION OF CONTRACT, TORT,
 * OR OTHERWISE ARISING FROM, OUT OF, OR IN CONNECTION WITH THE WORK OR THE USE
 * OF OR OTHER DEALINGS IN THE WORK.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pfxtree.h"

static int
check_entry(const struct pt_entry *entry, void *data)
{
	if (PT_TYPE_PTR == entry->type)
		assert(entry->data.p == data);

	return 0;
}

int
main(void)
{
	PrefixTree *p = pt_new(), *p2;
	void *dummy;
	assert(p != NULL);

	assert(0 == pt_add(p, "hello", 1));
	assert(0 == pt_add(p, "world", 2));
	assert(0 == pt_add(p, "henlo", 3));
	assert(0 == pt_add(p, "hell", -1));

	assert(PT_TYPE_INT == pt_data_type(pt_search(p, "hell")));
	assert(-1 == pt_data(pt_search(p, "hell")));

	assert(0 == pt_del(p, "hello"));
	assert(NULL == pt_search(p, "hello"));
	assert(pt_search(p, "hell") != NULL);

	dummy = malloc(16);
	assert(dummy != NULL);
	assert(0 == pt_add_p(p, "hello", dummy));
	assert(PT_TYPE_PTR == pt_data_type(pt_search(p, "hello")));

	assert(PT_ENOWORD == pt_del(p, "asdf"));

	pt_foreach(p, check_entry, dummy);

	p2 = pt_copy(p);
	assert(p2 != NULL);
	assert(pt_data_p(pt_search(p2, "hello")) == dummy);

	pt_deep_free(p, true);
	pt_deep_free(p2, false);
	return 0;
}
