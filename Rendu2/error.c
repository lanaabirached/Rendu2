/*
 * mac_error.h
 * UNOFFICIAL: create to use error.h module with on Mac OS X
 * created by Lana Abi Rached and Vianney Rousset
 *
 * project:			  jeu de réflexion
 * version:			  1.0
 * last modification: 2014-03-16
 * responsable:		  R. Boulic
 */

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error_pseudo_is_too_long(PlayerId player_id)
{
	printf("ERROR: player #%d pseudo is too long.\n", player_id);
}

void error_energy_is_negative(PlayerId player_id)
{
	printf("ERROR: player #%d energy is negative.\n", player_id);
}

void error_energy_is_too_big(PlayerId player_id)
{
	printf("ERROR: player #%d energy is too big.\n", player_id);
}

void error_too_many_disks(PlayerId player_id)
{
	printf("ERROR: player #%d number of disks is too damn hight!\n", player_id);
}

void error_missing_disk(PlayerId player_id)
{
	printf("ERROR: disks missing player #%d.\n", player_id);
}

void error_disk_is_out_of_boundaries(PlayerId player_id, int disk_index)
{
	printf("ERROR: player #%d disk #%d is out of boundaries\n", player_id, disk_index);
}

void error_disks_are_in_contact(PlayerId disk1_owner_id, int disk1_index,
								PlayerId disk2_owner_id, int disk2_index)
{
	printf("ERROR: player #%d disk #%d is intercepting player #%d disk #%d\n",
		   disk1_owner_id, disk1_index, disk2_owner_id, disk2_index);
}

void error_success(void)
{
	printf("** PARSER SUCCESS **\n");
}