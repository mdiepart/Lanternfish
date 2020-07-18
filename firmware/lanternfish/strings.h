#ifndef STRINGS_H
#define STRINGS_H

#if defined(ENGLISH) || !defined(FRENCH)
  #define STR_ERROR     "ERROR"
	#define STR_SETTINGS 	"Settings"
	#define STR_TIME 		"Set time"
	#define STR_DAY			"Day" 
  #define STR_MON     "Monday"
  #define STR_TUE     "Tuesday"
  #define STR_WED     "Wednesday"
  #define STR_THU     "Thursday"
  #define STR_FRI     "Friday"
  #define STR_SAT     "Saturday"
  #define STR_SUN     "Sunday"
  #define STR_RESET   "Reset"
#elif defined(FRENCH)
  #define STR_ERROR     "ERREUR"
	#define STR_SETTINGS 	"Paramètres"
	#define STR_TIME 		"Régler l'heure"
	#define STR_DAY			"Jour"
  #define STR_MON     "Lundi"
  #define STR_TUE     "Mardi"
  #define STR_WED     "Mercredi"
  #define STR_THU     "Jeudi"
  #define STR_FRI     "Vendredi"
  #define STR_SAT     "Samedi"
  #define STR_SUN     "Dimanche"
  #define STR_RESET   "Reset"

#endif

#endif
