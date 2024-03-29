/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/shell/shell.h>
#include <zephyr/logging/log_ctrl.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_internal.h>
#include <string.h>

typedef int (*log_backend_cmd_t)(const struct shell *shell,
				 const struct log_backend *backend,
				 size_t argc,
				 char **argv);

static const char * const severity_lvls[] = {
	"none",
	"err",
	"wrn",
	"inf",
	"dbg",
};

static const char * const severity_lvls_sorted[] = {
	"dbg",
	"err",
	"inf",
	"none",
	"wrn",
};

/**
 * @brief Function for finding backend instance with given name.
 *
 * @param p_name Name of the backend instance.
 *
 * @return Pointer to the instance or NULL.
 *
 */
static const struct log_backend *backend_find(char const *name)
{
	size_t slen = strlen(name);

	STRUCT_SECTION_FOREACH(log_backend, backend) {
		if (strncmp(name, backend->name, slen) == 0) {
			return backend;
		}
	}

	return NULL;
}

static bool shell_state_precheck(const struct shell *shell)
{
	if (shell->log_backend->control_block->state
				== SHELL_LOG_BACKEND_UNINIT) {
		shell_error(shell, "Shell log backend not initialized.");
		return false;
	}

	return true;
}

/**
 * @brief Function for executing command on given backend.
 */
static int shell_backend_cmd_execute(const struct shell *shell,
				     size_t argc,
				     char **argv,
				     log_backend_cmd_t func)
{
	/* Based on the structure of backend commands, name of the backend can
	 * be found at -1 (log backend <name> command).
	 */
	char const *name = argv[-1];
	const struct log_backend *backend = backend_find(name);

	if (backend != NULL) {
		func(shell, backend, argc, argv);
	} else {
		shell_error(shell, "Invalid backend: %s", name);
		return -ENOEXEC;
	}
	return 0;
}


static int log_status(const struct shell *shell,
		      const struct log_backend *backend,
		      size_t argc, char **argv)
{
	uint32_t modules_cnt = log_src_cnt_get(Z_LOG_LOCAL_DOMAIN_ID);
	uint32_t dynamic_lvl;
	uint32_t compiled_lvl;

	if (!log_backend_is_active(backend)) {
		shell_warn(shell, "Logs are halted!");
	}

	shell_fprintf(shell, SHELL_NORMAL, "%-40s | current | built-in \r\n",
					   "module_name");
	shell_fprintf(shell, SHELL_NORMAL,
	      "----------------------------------------------------------\r\n");

	for (int16_t i = 0U; i < modules_cnt; i++) {
		dynamic_lvl = log_filter_get(backend, Z_LOG_LOCAL_DOMAIN_ID,
					     i, true);
		compiled_lvl = log_filter_get(backend, Z_LOG_LOCAL_DOMAIN_ID,
					      i, false);

		shell_fprintf(shell, SHELL_NORMAL, "%-40s | %-7s | %s\r\n",
			      log_source_name_get(Z_LOG_LOCAL_DOMAIN_ID, i),
			      severity_lvls[dynamic_lvl],
			      severity_lvls[compiled_lvl]);
	}
	return 0;
}


static int cmd_log_self_status(const struct shell *shell,
			       size_t argc, char **argv)
{
	if (!shell_state_precheck(shell)) {
		return 0;
	}

	log_status(shell, shell->log_backend->backend, argc, argv);
	return 0;
}

static int cmd_log_backend_status(const struct shell *shell,
				  size_t argc, char **argv)
{
	shell_backend_cmd_execute(shell, argc, argv, log_status);
	return 0;
}

static int module_id_get(const char *name)
{
	uint32_t modules_cnt = log_src_cnt_get(Z_LOG_LOCAL_DOMAIN_ID);
	const char *tmp_name;
	uint32_t i;

	for (i = 0U; i < modules_cnt; i++) {
		tmp_name = log_source_name_get(Z_LOG_LOCAL_DOMAIN_ID, i);

		if (strncmp(tmp_name, name, 64) == 0) {
			return i;
		}
	}
	return -1;
}

static void filters_set(const struct shell *shell,
			const struct log_backend *backend,
			size_t argc, char **argv, uint32_t level)
{
	int i;
	int id;
	bool all = argc ? false : true;
	int cnt = all ? log_src_cnt_get(Z_LOG_LOCAL_DOMAIN_ID) : argc;

	if (!backend->cb->active) {
		shell_warn(shell, "Backend not active.");
	}

	for (i = 0; i < cnt; i++) {
		id = all ? i : module_id_get(argv[i]);
		if (id >= 0) {
			uint32_t set_lvl = log_filter_set(backend,
						       Z_LOG_LOCAL_DOMAIN_ID,
						       id, level);

			if (set_lvl != level) {
				const char *name;

				name = all ?
					log_source_name_get(Z_LOG_LOCAL_DOMAIN_ID, i) :
					argv[i];
				shell_warn(shell, "%s: level set to %s.",
					   name, severity_lvls[set_lvl]);
			}
		} else {
			shell_error(shell, "%s: unknown source name.", argv[i]);
		}
	}
}

static int severity_level_get(const char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(severity_lvls); i++) {
		if (strncmp(str, severity_lvls[i], 4) == 0) {
			return i;
		}
	}

	return -1;
}
static int log_enable(const struct shell *shell,
		      const struct log_backend *backend,
		      size_t argc,
		      char **argv)
{
	int severity_level;

	severity_level = severity_level_get(argv[1]);

	if (severity_level < 0) {
		shell_error(shell, "Invalid severity: %s", argv[1]);
		return -ENOEXEC;
	}

	/* Arguments following severity level are interpreted as module names.*/
	filters_set(shell, backend, argc - 2, &argv[2], severity_level);
	return 0;
}

static int cmd_log_self_enable(const struct shell *shell,
			       size_t argc, char **argv)
{
	if (!shell_state_precheck(shell)) {
		return 0;
	}

	return log_enable(shell, shell->log_backend->backend, argc, argv);
}

static int cmd_log_backend_enable(const struct shell *shell,
				  size_t argc, char **argv)
{
	return shell_backend_cmd_execute(shell, argc, argv, log_enable);
}

static int log_disable(const struct shell *shell,
		       const struct log_backend *backend,
		       size_t argc,
		       char **argv)
{
	filters_set(shell, backend, argc - 1, &argv[1], LOG_LEVEL_NONE);
	return 0;
}

static int cmd_log_self_disable(const struct shell *shell,
				 size_t argc, char **argv)
{
	if (!shell_state_precheck(shell)) {
		return 0;
	}

	return log_disable(shell, shell->log_backend->backend, argc, argv);
}

static int cmd_log_backend_disable(const struct shell *shell,
				   size_t argc, char **argv)
{
	return shell_backend_cmd_execute(shell, argc, argv, log_disable);
}

static void module_name_get(size_t idx, struct shell_static_entry *entry);

SHELL_DYNAMIC_CMD_CREATE(dsub_module_name, module_name_get);

static void module_name_get(size_t idx, struct shell_static_entry *entry)
{
	entry->handler = NULL;
	entry->help  = NULL;
	entry->subcmd = &dsub_module_name;
	entry->syntax = log_source_name_get(Z_LOG_LOCAL_DOMAIN_ID, idx);
}


static void severity_lvl_get(size_t idx, struct shell_static_entry *entry)
{
	entry->handler = NULL;
	entry->help  = NULL;
	entry->subcmd = &dsub_module_name;
	entry->syntax = (idx < ARRAY_SIZE(severity_lvls_sorted)) ?
					severity_lvls_sorted[idx] : NULL;
}

SHELL_DYNAMIC_CMD_CREATE(dsub_severity_lvl, severity_lvl_get);

static int log_halt(const struct shell *shell,
		    const struct log_backend *backend,
		    size_t argc,
		    char **argv)
{
	log_backend_deactivate(backend);
	return 0;
}


static int cmd_log_self_halt(const struct shell *shell,
			      size_t argc, char **argv)
{
	if (!shell_state_precheck(shell)) {
		return 0;
	}

	return log_halt(shell, shell->log_backend->backend, argc, argv);
}

static int cmd_log_backend_halt(const struct shell *shell,
				size_t argc, char **argv)
{
	return shell_backend_cmd_execute(shell, argc, argv, log_halt);
}

static int log_go(const struct shell *shell,
		  const struct log_backend *backend,
		  size_t argc,
		  char **argv)
{
	log_backend_activate(backend, backend->cb->ctx);
	return 0;
}


static int cmd_log_self_go(const struct shell *shell,
			   size_t argc, char **argv)
{
	if (!shell_state_precheck(shell)) {
		return 0;
	}

	return log_go(shell, shell->log_backend->backend, argc, argv);
}

static int cmd_log_backend_go(const struct shell *shell,
			      size_t argc, char **argv)
{
	return shell_backend_cmd_execute(shell, argc, argv, log_go);
}


static int cmd_log_backends_list(const struct shell *shell,
				 size_t argc, char **argv)
{
	STRUCT_SECTION_FOREACH(log_backend, backend) {
		shell_fprintf(shell, SHELL_NORMAL,
			      "%s\r\n"
			      "\t- Status: %s\r\n"
			      "\t- ID: %d\r\n\r\n",
			      backend->name,
			      backend->cb->active ? "enabled" : "disabled",
			      backend->cb->id);

	}
	return 0;
}

static int cmd_log_mem(const struct shell *sh, size_t argc, char **argv)
{
	uint32_t size;
	uint32_t used;
	uint32_t max;
	int err;

	err = log_mem_get_usage(&size, &used);
	if (err < 0) {
		shell_error(sh, "Failed to get usage (mode does not support it?)");
		return -ENOEXEC;
	}

	shell_print(sh, "Log message buffer utilization report:");
	shell_print(sh, "\tCapacity: %u bytes", size);
	shell_print(sh, "\tCurrently in use: %u bytes", used);

	err = log_mem_get_max_usage(&max);
	if (err < 0) {
		shell_print(sh, "Enable CONFIG_LOG_MEM_UTILIZATION to get maximum usage");
		return 0;
	}

	shell_print(sh, "\tMaximum usage: %u bytes", max);

	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_log_backend,
	SHELL_CMD_ARG(disable, &dsub_module_name,
		  "'log disable <module_0> .. <module_n>' disables logs in "
		  "specified modules (all if no modules specified).",
		  cmd_log_backend_disable, 2, 255),
	SHELL_CMD_ARG(enable, &dsub_severity_lvl,
		  "'log enable <level> <module_0> ...  <module_n>' enables logs"
		  " up to given level in specified modules (all if no modules "
		  "specified).",
		  cmd_log_backend_enable, 2, 255),
	SHELL_CMD(go, NULL, "Resume logging", cmd_log_backend_go),
	SHELL_CMD(halt, NULL, "Halt logging", cmd_log_backend_halt),
	SHELL_CMD(status, NULL, "Logger status", cmd_log_backend_status),
	SHELL_SUBCMD_SET_END
);

static void backend_name_get(size_t idx, struct shell_static_entry *entry)
{
	entry->handler = NULL;
	entry->help  = NULL;
	entry->subcmd = &sub_log_backend;
	entry->syntax  = NULL;

	STRUCT_SECTION_FOREACH(log_backend, backend) {
		entry->syntax = backend->name;
	}
}

SHELL_DYNAMIC_CMD_CREATE(dsub_backend_name_dynamic, backend_name_get);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_log_stat,
	SHELL_CMD(backend, &dsub_backend_name_dynamic, "Logger backends commands.", NULL),
	SHELL_COND_CMD_ARG(CONFIG_SHELL_LOG_BACKEND, disable, &dsub_module_name,
			   "'log disable <module_0> .. <module_n>' disables logs in specified "
			   "modules (all if no modules specified).",
			   cmd_log_self_disable, 1, 255),
	SHELL_COND_CMD_ARG(CONFIG_SHELL_LOG_BACKEND, enable, &dsub_severity_lvl,
			   "'log enable <level> <module_0> ...  <module_n>' enables logs up to"
			   " given level in specified modules (all if no modules specified).",
			   cmd_log_self_enable, 2, 255),
	SHELL_COND_CMD(CONFIG_SHELL_LOG_BACKEND, go, NULL, "Resume logging", cmd_log_self_go),
	SHELL_COND_CMD(CONFIG_SHELL_LOG_BACKEND, halt, NULL, "Halt logging", cmd_log_self_halt),
	SHELL_CMD_ARG(list_backends, NULL, "Lists logger backends.", cmd_log_backends_list, 1, 0),
	SHELL_COND_CMD(CONFIG_SHELL_LOG_BACKEND, status, NULL, "Logger status",
		       cmd_log_self_status),
	SHELL_COND_CMD(CONFIG_LOG_MODE_DEFERRED, mem, NULL, "Logger memory usage",
		       cmd_log_mem),
	SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(log, &sub_log_stat, "Commands for controlling logger",
		   NULL);
