# include <game/action.h>
# include <game/armor.h>
# include <game/description.h>
# include <game/message.h>
# include <game/thing.h>

inherit LIB_ACTION;
inherit UTIL_DESCRIPTION;
inherit UTIL_MESSAGE;

int weapon_;

static void create(object LIB_WEAPON* weapons)
{
    weapon_ = object_number(weapons[0]);
}

void perform(object LIB_CREATURE actor)
{
    object LIB_WEAPON weapon;

    weapon = find_object(weapon_);
    if (!weapon || (object LIB_THING) environment(weapon) != actor) {
        tell_object(actor, "You do not have that.");
        return;
    }

    if (!sizeof(actor->query_wielded() & ({ weapon }))) {
        tell_object(actor, "You are not wielding that.");
        return;
    }

    actor->remove_wielded(weapon);
    tell_object(actor, "You release " + definite_description(weapon, actor)
                + ".");
    tell_audience(actor, definite_description(actor) + " releases "
                  + indefinite_description(weapon) + ".");
}
