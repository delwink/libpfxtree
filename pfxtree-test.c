/*
 *  pfxtree-test - Delwink prefix tree library unit test
 *  Copyright (C) 2017 Delwink, LLC
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3 only.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pfxtree.h"

int
main(void)
{
	PrefixTree *p = pt_new();
	assert(p != NULL);

	assert(0 == pt_add(p, "hello", 1));
	assert(0 == pt_add(p, "world", 2));
	assert(0 == pt_add(p, "hell", -1));

	assert('i' == pt_data_type(pt_search(p, "hell")));
	assert(-1 == pt_data(pt_search(p, "hell")));

	assert(0 == pt_del(p, "hello"));
	assert(NULL == pt_search(p, "hello"));
	assert(pt_search(p, "hell") != NULL);

	void *dummy = malloc(0xDFDF);
	assert(dummy != NULL);
	assert(0 == pt_add_p(p, "hello", dummy));
	assert('p' == pt_data_type(pt_search(p, "hello")));

	assert(PT_ENOWORD == pt_del(p, "asdf"));

	pt_deep_free(p, true);
	return 0;
}
