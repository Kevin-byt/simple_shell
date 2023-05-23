#include "shell.h"

/**
 * shell_get_history_file - history file
 * @inf: struct of parameter
 *
 * Return: allocated string containg history file
 */

char *shell_get_history_file(info_t *inf)
{
	char *buffe, *fold;

	fold = _shellgetenv(inf, "HOME=");
	if (!fold)
		return (NULL);
	buffe = malloc(sizeof(char) * (sh_strlen(fold) + sh_strlen(HIST_FILE) + 2));
	if (!buffe)
		return (NULL);
	buffe[0] = 0;
	_shell_strcpy(buffe, fold);
	sh_strcat(buffe, "/");
	sh_strcat(buffe, HIST_FILE);
	return (buffe);
}

/**
 * shell_rd_history - reads file history
 * @inf: struct of parameter
 * Return: histcount on success, 0 otherwise
 */
int shell_rd_history(info_t *inf)
{
	int x, fin = 0;
	int ln_cnt = 0;
	ssize_t fl_sz, read_ln, fl_d = 0;
	struct stat st;
	char *buffe = NULL, *fl_Name = shell_get_history_file(inf);

	if (!fl_Name)
		return (0);

	fl_d = open(fl_Name, O_RDONLY);
	free(fl_Name);
	if (fl_d == -1)
		return (0);
	if (!fstat(fl_d, &st))
		fl_sz = st.st_size;
	if (fl_sz < 2)
		return (0);
	buffe = malloc(sizeof(char) * (fl_sz + 1));
	if (!buffe)
		return (0);
	read_ln = read(fl_d, buffe, fl_sz);
	buffe[fl_sz] = 0;
	if (read_ln <= 0)
		return (free(buffe), 0);
	close(fl_d);
	for (x = 0; x < fl_sz; x++)
		if (buffe[x] == '\n')
		{
			buffe[x] = 0;
			shell_bld_hist_list(inf, buffe + fin, ln_cnt++);
			fin = x + 1;
		}
	if (fin != x)
		shell_bld_hist_list(inf, buffe + fin, ln_cnt++);
	free(buffe);
	inf->sh_hist_cnt = ln_cnt;
	while (inf->sh_hist_cnt-- >= HIST_MAX)
		index_delete_node(&(inf->sh_hist_node), 0);
	shell_renum_history(inf);
	return (inf->sh_hist_cnt);
}

/**
 * shell_wr_history - writes the history
 * @inf: struct of parameter
 * Return: 1 - success, else -1
 */

int shell_wr_history(info_t *inf)
{
	ssize_t fld;
	list_t *nd = NULL;
	char *flName = shell_get_history_file(inf);

	if (!flName)
		return (-1);

	fld = open(flName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(flName);
	if (fld == -1)
		return (-1);
	for (nd = inf->sh_hist_node; nd; nd = nd->next)
	{
		_shellputsfd(nd->str, fld);
		_shellputfd('\n', fld);
	}
	_shellputfd(BUF_FLUSH, fld);
	close(fld);
	return (1);
}

/**
 * shell_renum_history - renumbers the history linked list after changes
 * @inf: potential arguments structure
 * Return: new count
 */

int shell_renum_history(info_t *inf)
{
	list_t *node = inf->sh_hist_node;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->sh_hist_cnt = i);
}

/**
 * shell_bld_hist_list - history linked list add entry
 * @inf: potential arguments structure
 * @buffe: buffer
 * @ln_cnt: the history linecount
 * Return: 0 - Always
 */

int shell_bld_hist_list(info_t *inf, char *buffe, int ln_cnt)
{
	list_t *nd = NULL;

	if (inf->sh_hist_node)
		nd = inf->sh_hist_node;
	sh_add_node_end(&nd, buffe, ln_cnt);

	if (!inf->sh_hist_node)
		inf->sh_hist_node = nd;
	return (0);
}
