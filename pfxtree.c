/*
 *  libpfxtree - Delwink prefix tree library
 *  Copyright (C) 2015, 2017 Delwink, LLC
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

#include <stdlib.h>
#include <string.h>

#include "pfxtree.h"

#define pt_child_foreach(S,C) for ((C) = (S)->children;			\
				   (C) != NULL; (C) = (C)->next)

PrefixTree *
pt_new()
{
	PrefixTree *self = malloc(sizeof(PrefixTree));
	if (!self)
		return NULL;

	self->ch = '\0';
	self->type = '\0';
	self->data.i = 0;
	self->parent = NULL;
	self->children = NULL;
	self->next = NULL;

	return self;
}

void
pt_free(PrefixTree *self)
{
	pt_deep_free(self, false);
}

void
pt_deep_free(PrefixTree *self, bool free_data)
{
	PrefixTree *child, *next = NULL;
	for (child = self->children; child != NULL; child = next)
	{
		if (free_data && 'p' == child->type && child->data.p != NULL)
			free(child->data.p);

		next = child->next;
		pt_deep_free(child, free_data);
	}

	free(self);
}

static PrefixTree *
get_last_child(const PrefixTree *self)
{
	PrefixTree *child;
	pt_child_foreach(self, child)
	{
		if (!child->next)
			return child;
	}

	return NULL;
}

static PrefixTree *
get_child_by_ch(const PrefixTree *self, const char ch)
{
	PrefixTree *child;
	pt_child_foreach(self, child)
	{
		if (ch == child->ch)
			return child;
	}

	return NULL;
}

static int
add(PrefixTree *self, const char *word, union _pt_data data, char type)
{
	int rc = 0;
	PrefixTree *node = self;
	size_t i, len = strlen(word);

	for (i = 0; i <= len; ++i)
	{
		PrefixTree *child = get_child_by_ch(node, word[i]);
		if (!child)
			break;

		node = child;
	}

	PrefixTree *first_insertion = NULL;

	for (; i <= len; ++i)
	{
		PrefixTree *new = pt_new();
		if (!new)
		{
			rc = PT_EALLOC;
			break;
		}

		new->ch = word[i];
		new->parent = node;

		PrefixTree *end = get_last_child(node);
		if (!end)
			node->children = new;
		else
			end->next = new;

		if (!first_insertion)
			first_insertion = new;

		node = new;
	}

	if (rc)
	{
		pt_free(first_insertion);
		return rc;
	}

	node->data = data;
	node->type = type;

	return rc;
}

int
pt_add(PrefixTree *self, const char *word, int data)
{
	union _pt_data d;
	d.i = data;
	return add(self, word, d, 'i');
}

int
pt_add_p(PrefixTree *self, const char *word, void *data)
{
	union _pt_data d;
	d.p = data;
	return add(self, word, d, 'p');
}

static size_t
num_children(PrefixTree *self)
{
	if (!self->children)
		return 0;

	size_t i;
	self = self->children;
	for (i = 1; self->next; ++i)
		self = self->next;

	return i;
}

int
pt_del(PrefixTree *self, const char *word)
{
	PrefixTree *p = (PrefixTree *) pt_search(self, word);
	if (!p)
		return PT_ENOWORD;

	while (p->parent != NULL && num_children(p->parent) == 1)
		p = p->parent;

	if (p->parent)
	{
		if (p == p->parent->children)
		{
			p->parent->children = p->next;
		}
		else
		{
			PrefixTree *child = p->parent->children;
			while (child->next != p)
				child = child->next;

			child->next = p->next;
		}
	}
	else
	{
		p = p->children;
	}

	pt_deep_free(p, true);
	return 0;
}

int
pt_data(const PrefixTree *self)
{
	return self->data.i;
}

void *
pt_data_p(const PrefixTree *self)
{
	return self->data.p;
}

char
pt_data_type(const PrefixTree *self)
{
	return self->type;
}

const PrefixTree *
pt_search(const PrefixTree *root, const char *word)
{
	const PrefixTree *node = root;
	size_t i, len = strlen(word);

	for (i = 0; i <= len; ++i)
	{
		node = get_child_by_ch(node, word[i]);

		if (!node)
			return NULL;

		if ('\0' == node->ch)
			return node;
	}

	return NULL;
}

const char *
pt_version()
{
	return "0.3.0";
}
