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
 * @version 0.0
 * @date 09/05/2015
 * @author David McMackins II
 * @brief Delwink prefix tree (trie) library
 */

#ifndef DELWINK_PFXTREE_H
#define DELWINK_PFXTREE_H

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

/**
 * @brief A node in a prefix tree.
 */
typedef struct trie
{
  char ch;
  int data;

  struct trie *children;
  struct trie *next;
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
 * @brief Adds a new word to a prefix tree.
 * @param self The tree to which to add the word.
 * @param word The word to be added.
 * @param data A number to be associated with the word.
 * @return Nonzero if an error occurred.
 */
int
pt_add (PrefixTree *self, const char *word, int data);

/**
 * @brief Gets the data from a prefix tree node.
 * @param self The node from which to get the data.
 * @return self's data (default 0).
 */
int
pt_data (const PrefixTree *self);

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
