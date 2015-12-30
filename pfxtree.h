/*
 *  libpfxtree - Delwink prefix tree library
 *  Copyright (C) 2015 Delwink, LLC
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

/**
 * @file pfxtree.h
 * @version 0.2
 * @date 12/30/2015
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

/**
 * @brief Error codes possibly returned by functions in this library.
 */
enum pt_error
{
  PT_EALLOC = -1
};

union _pt_data
{
  int i;
  void *p;
};

/**
 * @brief A node in a prefix tree.
 */
typedef struct _pt_trie
{
  char ch;
  char type;
  union _pt_data data;

  struct _pt_trie *children;
  struct _pt_trie *next;
} PrefixTree;

/**
 * @brief Creates a new prefix tree.
 * @return Pointer to the root node of the tree or NULL on failure.
 */
PrefixTree *
pt_new (void);

/**
 * @brief Frees an allocated prefix tree (and its child nodes).
 * @param self The tree to free.
 */
void
pt_free (PrefixTree *self);

/**
 * @brief Frees an allocated prefix tree (and its child nodes) and optionally
 * its referenced data.
 * @param self The tree to free.
 * @param free_data Whether to free memory pointed to by the data (if pointer).
 */
void
pt_deep_free (PrefixTree *self, bool free_data);

/**
 * @brief Adds a new word to a prefix tree with integer data.
 * @param self The tree to which to add the word.
 * @param word The word to be added.
 * @param data A number to be associated with the word.
 * @return Nonzero if an error occurred.
 */
int
pt_add (PrefixTree *self, const char *word, int data);

/**
 * @brief Adds a new word to a prefix tree with pointer data.
 * @param self The tree to which to add the word.
 * @param word The word to be added.
 * @param data A pointer to be associated with the word.
 * @return Nonzero if an error occurred.
 */
int
pt_add_p (PrefixTree *self, const char *word, void *data);

/**
 * @brief Gets the integer data from a prefix tree node.
 * @param self The node from which to get the data.
 * @return self's data (default 0).
 */
int
pt_data (const PrefixTree *self);

/**
 * @brief Gets the pointer data from a prefix tree node.
 * @param self The node from which to get the data.
 * @return self's data (default NULL).
 */
void *
pt_data_p (const PrefixTree *self);

/**
 * @brief Gets the type of the data stored in the prefix tree node.
 * @param self The node whose type is to be examined.
 * @return 'i' if integer, 'p' if pointer, or '\0' if no data.
 */
char
pt_data_type (const PrefixTree *self);

/**
 * @brief Searches for a word in a prefix tree.
 * @param root The node from which to begin the search.
 * @param word The word for which to search.
 * @return Pointer to the data-storing node of the word or NULL if not found.
 */
const PrefixTree *
pt_search (const PrefixTree *root, const char *word);

/**
 * @brief Checks the current version of the library.
 * @return A version string for this libpfxtree installation.
 */
const char *
pt_version (void);

__END_DECLS

#endif
