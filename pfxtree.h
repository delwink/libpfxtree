/*
 *  libpfxtree - Delwink prefix tree library
 *  Copyright (C) 2015, 2017, 2020 Delwink, LLC
 *
 *  Redistributions, modified or unmodified, in whole or in part, must retain
 *  applicable notices of copyright or other legal privilege, these conditions,
 *  and the following license terms and disclaimer.  Subject to these
 *  conditions, each holder of copyright or other legal privileges, author or
 *  assembler, and contributor of this work, henceforth "licensor", hereby
 *  grants to any person who obtains a copy of this work in any form:
 *
 *  1. Permission to reproduce, modify, distribute, publish, sell, sublicense,
 *  use, and/or otherwise deal in the licensed material without restriction.
 *
 *  2. A perpetual, worldwide, non-exclusive, royalty-free, gratis, irrevocable
 *  patent license to make, have made, provide, transfer, import, use, and/or
 *  otherwise deal in the licensed material without restriction, for any and
 *  all patents held by such licensor and necessarily infringed by the form of
 *  the work upon distribution of that licensor's contribution to the work
 *  under the terms of this license.
 *
 *  NO WARRANTY OF ANY KIND IS IMPLIED BY, OR SHOULD BE INFERRED FROM, THIS
 *  LICENSE OR THE ACT OF DISTRIBUTION UNDER THE TERMS OF THIS LICENSE,
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *  A PARTICULAR PURPOSE, AND NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS,
 *  ASSEMBLERS, OR HOLDERS OF COPYRIGHT OR OTHER LEGAL PRIVILEGE BE LIABLE FOR
 *  ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN ACTION OF CONTRACT,
 *  TORT, OR OTHERWISE ARISING FROM, OUT OF, OR IN CONNECTION WITH THE WORK OR
 *  THE USE OF OR OTHER DEALINGS IN THE WORK.
 */

/**
 * @file pfxtree.h
 * @version 0.4
 * @date 2/25/2020
 * @author David McMackins II
 * @brief Delwink prefix tree (trie) library
 */

#ifndef DELWINK_PFXTREE_H
#define DELWINK_PFXTREE_H

#include <stdbool.h>

#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

__BEGIN_DECLS

enum pt_data_type
{
	PT_TYPE_INT,
	PT_TYPE_PTR
};

/**
 * @brief Error codes possibly returned by functions in this library.
 */
enum pt_error
{
	PT_EALLOC  = -1,
	PT_ENOWORD = -2
};

union pt_data
{
	int i;
	void *p;
};

/**
 * @brief A node in a prefix tree.
 */
typedef struct _pt_trie
{
	union pt_data data;

	struct _pt_trie *parent;
	struct _pt_trie *children;
	struct _pt_trie *next;

	int ch;
	enum pt_data_type type;
} PrefixTree;

/**
 * @brief Creates a new prefix tree.
 * @return Pointer to the root node of the tree or NULL on failure.
 */
PrefixTree *
pt_new(void);

/**
 * @brief Copies a prefix tree.
 * @param src The prefix tree to be copied.
 * @return The copied tree, or NULL on failure.
 */
PrefixTree *
pt_copy(const PrefixTree *src);

/**
 * @brief Frees an allocated prefix tree (and its child nodes).
 * @param self The tree to free.
 */
void
pt_free(PrefixTree *self);

/**
 * @brief Frees an allocated prefix tree (and its child nodes) and optionally
 * its referenced data.
 * @param self The tree to free.
 * @param free_data Whether to free memory pointed to by the data (if pointer).
 */
void
pt_deep_free(PrefixTree *self, bool free_data);

/**
 * @brief Adds a new word to a prefix tree with integer data.
 * @param self The tree to which to add the word.
 * @param word The word to be added.
 * @param data A number to be associated with the word.
 * @return Nonzero if an error occurred.
 */
int
pt_add(PrefixTree *self, const char *word, int data);

/**
 * @brief Adds a new word to a prefix tree with pointer data.
 * @param self The tree to which to add the word.
 * @param word The word to be added.
 * @param data A pointer to be associated with the word.
 * @return Nonzero if an error occurred.
 */
int
pt_add_p(PrefixTree *self, const char *word, void *data);

/**
 * @brief Deletes a word from a prefix tree.
 * @param self The tree from which to delete the word.
 * @param word The word to be deleted.
 * @return Nonzero if word not found.
 */
int
pt_del(PrefixTree *self, const char *word);

/**
 * @brief Gets the integer data from a prefix tree node.
 * @param self The node from which to get the data.
 * @return self's data (default 0).
 */
int
pt_data(const PrefixTree *self);

/**
 * @brief Gets the pointer data from a prefix tree node.
 * @param self The node from which to get the data.
 * @return self's data (default NULL).
 */
void *
pt_data_p(const PrefixTree *self);

/**
 * @brief Gets the type of the data stored in the prefix tree node.
 * @param self The node whose type is to be examined.
 * @return 'i' if integer, 'p' if pointer, or '\0' if no data.
 */
int
pt_data_type(const PrefixTree *self);

/**
 * @brief Searches for a word in a prefix tree.
 * @param root The node from which to begin the search.
 * @param word The word for which to search.
 * @return Pointer to the data-storing node of the word or NULL if not found.
 */
const PrefixTree *
pt_search(const PrefixTree *root, const char *word);

struct pt_entry
{
	const char *word;
	union pt_data data;
	enum pt_data_type type;
};

/**
 * @brief Run an operation for each word in a prefix tree.
 * @param root The node from which to begin the search.
 * @param f The operation to be run, accepting the word, its data, and
 *          and arbitrary data; returns nonzero to break the loop.
 * @param data Data to be passed to f.
 * @return Nonzero on error, or nonzero return from f.
 */
int
pt_foreach(const PrefixTree *root, int (*f)(const struct pt_entry *,void *),
	void *data);

/**
 * @brief Checks the current version of the library.
 * @return A version string for this libpfxtree installation.
 */
const char *
pt_version(void);

__END_DECLS

#endif
