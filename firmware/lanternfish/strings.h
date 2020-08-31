#ifndef STRINGS_H
#define STRINGS_H

#if defined(ENGLISH) || !defined(FRENCH)
    #define STR_ERROR       "ERROR"
    #define STR_SETTINGS 	"Settings"
    #define STR_TIME 		"Set time"
    #define STR_DAY			"Day" 
    #define STR_MON         "Monday"
    #define STR_TUE         "Tuesday"
    #define STR_WED         "Wednesday"
    #define STR_THU         "Thursday"
    #define STR_FRI         "Friday"
    #define STR_SAT         "Saturday"
    #define STR_SUN         "Sunday"
    #define STR_RESET       "Reset"
    #define STR_CONF        "Confirm"
    #define STR_LP_CONF     "Lng pres to conf"
    #define STR_SCHEDULE    "Schedule"
    #define STR_DEL         "Delete"
    #define STR_POINT       "point"
    #define STR_ADD_PT      "Add new point"
    #define STR_HOUR        "Hour"
    #define STR_MINUTES     "Minutes"
    #define STR_POWER       "Power"

#elif defined(FRENCH)
    #define STR_ERROR       "ERREUR"
    #define STR_SETTINGS 	"Paramètres"
    #define STR_TIME 		"Régler l'heure"
    #define STR_DAY			"Jour"
    #define STR_MON         "Lundi"
    #define STR_TUE         "Mardi"
    #define STR_WED         "Mercredi"
    #define STR_THU         "Jeudi"
    #define STR_FRI         "Vendredi"
    #define STR_SAT         "Samedi"
    #define STR_SUN         "Dimanche"
    #define STR_RESET       "Réinitialisation"
    #define STR_CONF        "Confirmer"
    #define STR_LP_CONF     "App lng pr conf"
    #define STR_SCHEDULE    "Planning"
    #define STR_DEL         "Supprimer"
    #define STR_POINT       "point"
    #define STR_ADD_PT      "Ajouter point"
    #define STR_HOUR        "Heure"
    #define STR_MINUTES     "Minutes"
    #define STR_POWER       "Puissance"


#endif

#endif
