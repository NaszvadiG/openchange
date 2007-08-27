/*
 *  OpenChange Exchange Administration library.
 *
 *  Copyright (C) Julien Kerihuel 2007.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <libmapiadmin/libmapiadmin.h>
#include <libmapiadmin/proto_private.h>

_PUBLIC_ struct mapiadmin_ctx *mapiadmin_init(void)
{
	struct mapiadmin_ctx	*mapiadmin_ctx;

	if (!global_mapi_ctx) return NULL;
	if (!global_mapi_ctx->session) return NULL;
	if (!global_mapi_ctx->session->profile) return NULL;

	mapiadmin_ctx = talloc_zero((TALLOC_CTX *)global_mapi_ctx, struct mapiadmin_ctx);

	mapiadmin_ctx->binding = talloc_asprintf((TALLOC_CTX *)mapiadmin_ctx, "ncacn_np:%s", 
						 global_mapi_ctx->session->profile->server);

	return mapiadmin_ctx;
}

_PUBLIC_ enum MAPISTATUS mapiadmin_release(struct mapiadmin_ctx *mapiadmin_ctx)
{
	MAPI_RETVAL_IF(!mapiadmin_ctx, MAPI_E_NOT_INITIALIZED, NULL);

	talloc_free(mapiadmin_ctx);

	return MAPI_E_SUCCESS;
}
