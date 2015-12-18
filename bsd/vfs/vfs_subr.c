 * Copyright (c) 2000-2015 Apple Inc. All rights reserved.


		if (vfsp->vfc_mountroot == NULL)
		if ((error = (*vfsp->vfc_mountroot)(mp, rootvp, ctx)) == 0) {
			if ((mp->mnt_ioflags & MNT_IOFLAGS_FUSION_DRIVE) && 
			    (mp->mnt_ioflags & MNT_IOFLAGS_IOSCHED_SUPPORTED)) {
				/*
				 * only for CF
				 */
	mount_t nmp;
	TAILQ_FOREACH(nmp, &mountlist, mnt_list) {
		while (vfs_getvfs_locked(&tfsid)) {
			if (++mntid_gen == 0)
				mntid_gen++;
			tfsid.val[0] = makedev(nblkdev + mtype, mntid_gen);
		}
__private_extern__ int
is_package_name(const char *name, int len)
			break;
				break;
    
			} else {
    
			} else {

	kn->kn_flags |= EV_CLEAR;
			if ( !LIST_EMPTY(&vp->v_nclinks) || !LIST_EMPTY(&vp->v_ncchildren))


	uint32_t dfflags;	// Directory file flags
	/*
	 * Handle inheritance of restricted flag
	 */
	error = vnode_flags(dvp, &dfflags, ctx);
	if (error)
		return error;
	if (dfflags & SF_RESTRICTED)
		VATTR_SET(vap, va_flags, SF_RESTRICTED);
			!(vp->v_mount->mnt_vtable->vfc_vfsflags & VFC_VFSDIRLINKS)) {
int 
             struct vnode *tdvp,  struct vnode *tvp,  struct componentname *tcnp,
             vfs_context_t ctx, void *reserved)
		if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
			error = ENOTDIR;
			goto out;
		} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
			error = EISDIR;
			goto out;
	error = 0;
	if ((tvp != NULL) && vnode_isdir(tvp)) {
		if (tvp != fdvp)
			moving = 1;
	} else if (tdvp != fdvp) {
		moving = 1;
	}

	/*
	 * must have delete rights to remove the old name even in
	 * the simple case of fdvp == tdvp.
	 *
	 * If fvp is a directory, and we are changing it's parent,
	 * then we also need rights to rewrite its ".." entry as well.
	 */
	if (vnode_isdir(fvp)) {
		if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE | KAUTH_VNODE_ADD_SUBDIRECTORY, ctx)) != 0)
	} else {
		if ((error = vnode_authorize(fvp, fdvp, KAUTH_VNODE_DELETE, ctx)) != 0)
	}
	if (moving) {
		/* moving into tdvp or tvp, must have rights to add */
		if ((error = vnode_authorize(((tvp != NULL) && vnode_isdir(tvp)) ? tvp : tdvp,
						NULL, 
						vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE,
						ctx)) != 0) {
	} else {
		/* node staying in same directory, must be allowed to add new name */
		if ((error = vnode_authorize(fdvp, NULL,
						vnode_isdir(fvp) ? KAUTH_VNODE_ADD_SUBDIRECTORY : KAUTH_VNODE_ADD_FILE, ctx)) != 0)
	}
	/* overwriting tvp */
	if ((tvp != NULL) && !vnode_isdir(tvp) &&
			((error = vnode_authorize(tvp, tdvp, KAUTH_VNODE_DELETE, ctx)) != 0)) {
		goto out;
 * Deletion is not permitted if the directory is sticky and the caller is
 * not owner of the node or directory.
 * If either the node grants DELETE, or the directory grants DELETE_CHILD,
 * the node may be deleted.  If neither denies the permission, and the
 * caller has Posix write access to the directory, then the node may be
 * deleted.
 * on directories without the sticky bit set.
int
vnode_authorize_delete(vauth_ctx vcp, boolean_t cached_delete_child);
/*static*/ int
	int			error, delete_denied, delete_child_denied, ismember;
	/* check the ACL on the directory */
	delete_child_denied = 0;
	if (!cached_delete_child && VATTR_IS_NOT(dvap, va_acl, NULL)) {
		eval.ae_requested = KAUTH_VNODE_DELETE_CHILD;
		eval.ae_acl = &dvap->va_acl->acl_ace[0];
		eval.ae_count = dvap->va_acl->acl_entrycount;
		if (vauth_dir_owner(vcp))
		if ((error = vauth_dir_ingroup(vcp, &ismember, ENOENT)) != 0 && error != ENOENT)
			return(error);
		/*
		 * If there is no entry, we are going to defer to other
		 * authorization mechanisms.
		 */
		error = kauth_acl_evaluate(cred, &eval);

		if (error != 0) {
			return(error);
			delete_child_denied = 1;
			break;
			/* FALLSTHROUGH */
                case KAUTH_RESULT_ALLOW:
                        KAUTH_DEBUG("%p    ALLOWED - granted by directory ACL", vcp->vp);
                        return(0);
			/* Effectively the same as !delete_child_denied */
			KAUTH_DEBUG("%p    DEFERRED - directory ACL", vcp->vp);
	/* check the ACL on the node */
	delete_denied = 0;
	if (VATTR_IS_NOT(vap, va_acl, NULL)) {
		eval.ae_requested = KAUTH_VNODE_DELETE;
		eval.ae_acl = &vap->va_acl->acl_ace[0];
		eval.ae_count = vap->va_acl->acl_entrycount;
		if (vauth_file_owner(vcp))
		if ((error = vauth_file_ingroup(vcp, &ismember, ENOENT)) != 0 && error != ENOENT)
		if ((error = kauth_acl_evaluate(cred, &eval)) != 0) {
			return(error);

			delete_denied = 1;
			break;
			KAUTH_DEBUG("%p    ALLOWED - granted by file ACL", vcp->vp);
			return(0);
			/* Effectively the same as !delete_child_denied */
			KAUTH_DEBUG("%p    DEFERRED%s - by file ACL", vcp->vp, delete_denied ? "(DENY)" : "");
	/* if denied by ACL on directory or node, return denial */
	if (delete_denied || delete_child_denied) {
		KAUTH_DEBUG("%p    DENIED - denied by ACL", vcp->vp);
		return(EACCES);
		return(EACCES);
	}

	/* check the directory */
	if (!cached_delete_child && (error = vnode_authorize_posix(vcp, VWRITE, 1 /* on_dir */)) != 0) {
		KAUTH_DEBUG("%p    DENIED - denied by posix permisssions", vcp->vp);
		return(error);
	return(0);
	 * Get vnode attributes and extended security information for the vnode
	 * and directory if required.
	 */
	VATTR_WANTED(&va, va_mode);
	VATTR_WANTED(&va, va_uid);
	VATTR_WANTED(&va, va_gid);
	VATTR_WANTED(&va, va_flags);
	VATTR_WANTED(&va, va_acl);
	if ((result = vnode_getattr(vp, &va, ctx)) != 0) {
		KAUTH_DEBUG("%p    ERROR - failed to get vnode attributes - %d", vp, result);
		goto out;
	}
	if (dvp) {
		VATTR_WANTED(&dva, va_mode);
		VATTR_WANTED(&dva, va_uid);
		VATTR_WANTED(&dva, va_gid);
		VATTR_WANTED(&dva, va_flags);
		VATTR_WANTED(&dva, va_acl);
		if ((result = vnode_getattr(dvp, &dva, ctx)) != 0) {
			KAUTH_DEBUG("%p    ERROR - failed to get directory vnode attributes - %d", vp, result);
			goto out;
		}
	}

	/*
	 * If the vnode is an extended attribute data vnode (eg. a resource fork), *_DATA becomes
	 * *_EXTATTRIBUTES.
	 * Point 'vp' to the resource fork's parent for ACL checking
	if (vnode_isnamedstream(vp) &&
	    (vp->v_parent != NULL) &&
	    (vget_internal(vp->v_parent, 0, VNODE_NODEAD | VNODE_DRAINO) == 0)) {
		parent_ref = TRUE;
		vcp->vp = vp = vp->v_parent;
		if (VATTR_IS_SUPPORTED(&va, va_acl) && (va.va_acl != NULL))
			kauth_acl_free(va.va_acl);
		VATTR_INIT(&va);
		VATTR_WANTED(&va, va_mode);
		VATTR_WANTED(&va, va_flags);
		if ((result = vnode_getattr(vp, &va, ctx)) != 0)
	if (!vfs_context_issuser(ctx)) {
	if ((rights & KAUTH_VNODE_DELETE) && parent_authorized_for_delete_child == FALSE) {
	        /*
		 * parent was successfully and newly authorized for content deletions
		 * add it to the cache, but only if it doesn't have the sticky
		 * bit set on it.  This same  check is done earlier guarding
		 * fetching of dva, and if we jumped to out without having done
		 * this, we will have returned already because of a non-zero
		 * 'result' value.
		 */
		if (VATTR_IS_SUPPORTED(&dva, va_mode) &&
		    !(dva.va_mode & (S_ISVTX))) {
		    	/* OK to cache delete rights */
			KAUTH_DEBUG("%p - caching DELETE_CHILD rights", dvp);
			vnode_cache_authorized_action(dvp, ctx, KAUTH_VNODE_DELETE_CHILD);
		}
	}
	int		has_priv_suser, ismember, defaulted_owner, defaulted_group, defaulted_mode;
			struct vnode_attr dva;
			VATTR_INIT(&dva);
			VATTR_WANTED(&dva, va_gid);
			if ((error = vnode_getattr(dvp, &dva, ctx)) != 0)
				goto out;
	
			/* clear set-uid and set-gid bits as required by Posix */
			if (VATTR_IS_ACTIVE(vap, va_mode)) {
				newmode = vap->va_mode;
			} else if (VATTR_IS_SUPPORTED(&ova, va_mode)) {
				newmode = ova.va_mode;
			} else {
				KAUTH_DEBUG("CHOWN - trying to change owner but cannot get mode from filesystem to mask setugid bits");
				newmode = 0;
			}
			if (newmode & (S_ISUID | S_ISGID)) {
				VATTR_SET(vap, va_mode, newmode & ~(S_ISUID | S_ISGID));
				KAUTH_DEBUG("CHOWN - masking setugid bits from mode %o to %o", newmode, vap->va_mode);