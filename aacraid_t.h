
#ifndef __AACRAID_H__
#define __AACRAID_H__




struct aac_dev
{
	struct list_head	entry;
	const char		*name;
	int			id;
};


#endif 
