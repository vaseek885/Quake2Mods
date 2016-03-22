// + THIS ENTIRE CODE BLOCK IS NEW!
/* v_sabdrop.c - Vnsaf
===========================
Provides a method to allow users to sabotage and drop weapons
Last modified 12/25/97
*/

#include "g_local.h"   //Included so we'll have access to needed variables
#include "v_sabdrop.h" //The forward declaration of our function


/*
=================
Cmd_SabDrop_f

Modified from Cmd_InvDrop_f by V 12/24
Drop an inventory weapon. Meant to be bound to a key.
=================
*/
void Cmd_SabDrop_f(edict_t *ent)	//Acting on an entity
{
	int		index;

	if ((int)(dmflags->value) & DF_WEAPONS_STAY)
		return;
	gitem_t * item = ent->client->pers.weapon;
	index = ITEM_INDEX(item);
	// see if we're already using it
	gi.cprintf(ent, PRINT_HIGH, "Trying to drop :%s\n", item->pickup_name);
	if (item->pickup_name == "Grenades"){
		gitem_t *it = FindItem("Grenades");
		int stacks = (ent->client->pers.inventory[ITEM_INDEX(it)] / 5);
		for (int i = 0; i < stacks; i++){
			Drop_Item(ent, it);
		}
		ent->client->pers.inventory[ITEM_INDEX(it)] = 0;
		NoAmmoWeaponChange(ent);
	}
	if (((item == ent->client->pers.weapon) || (item == ent->client->newweapon)) && (ent->client->pers.inventory[index] == 1))
	{
		if (item->drop){ 
			int index2;
			gitem_t *it;
			it = FindItem("Blaster");
			if (!it)
			{
				gi.cprintf(ent, PRINT_HIGH, "unknown item: %s\n", "Blaster");
				return;
			}
			if (!it->use)
			{
				gi.cprintf(ent, PRINT_HIGH, "Item is not usable.\n");
				return;
			}
			index2 = ITEM_INDEX(it);
			if (!ent->client->pers.inventory[index2])
			{
				gi.cprintf(ent, PRINT_HIGH, "Out of item: %s\n", "Blaster");
				return;
			}
			it->use(ent, it);
			Drop_Item(ent, item);
			ent->client->pers.inventory[index]--;
		}
		else
		{
			gi.cprintf(ent, PRINT_HIGH, "Not Droppable!");
		}
	}

}

// + END OF NEW CODE BLOCK