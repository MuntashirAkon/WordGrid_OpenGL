/**
 * External resources such as music or images.
 * 
 * Author: Muntashir Al-Islam <muntashirakon@riseup.net>
 */

#ifndef _H_RESOURCES
#define _H_RESOURCES

#include "playsound.h"

#define playBackgroundMusic playWav("music//back.wav", NULL, SND_FILENAME | SND_ASYNC)
#define playKeyboardMusic playWav("music//enter.wav", NULL, SND_FILENAME | SND_ASYNC)
#define playMouseClickMusic playWav("music//click.wav", NULL, SND_FILENAME | SND_ASYNC)
#define playNavigationMusic playWav("music//move.wav", NULL, SND_FILENAME | SND_ASYNC)

#define MAX_WORD_SIZE 800
#define MAX_WORD_LEN 20

// Source: Oxford 3000 words
const char word[MAX_WORD_SIZE][MAX_WORD_LEN] = {"account", "act", "addition", "adjustment", "advertisement", "agreement", "air", "amount", "amusement", "animal", "answer", "apparatus", "approval", "argument", "art", "attack", "attempt", "attention", "attraction", "authority", "back", "balance", "base", "behavior", "belief", "birth", "bit", "bite", "blood", "blow", "body", "brass", "bread", "breath", "brother", "building", "burn", "burst", "business", "butter", "canvas", "care", "cause", "chalk", "chance", "change", "cloth", "coal", "color", "comfort", "committee", "company", "comparison", "competition", "condition", "connection", "control", "cook", "copper", "copy", "cork", "cotton", "cough", "country", "cover", "crack", "credit", "crime", "crush", "cry", "current", "curve", "damage", "danger", "daughter", "day", "death", "debt", "decision", "degree", "design", "desire", "destruction", "detail", "development", "digestion", "direction", "discovery", "discussion", "disease", "disgust", "distance", "distribution", "division", "doubt", "drink", "driving", "dust", "earth", "edge", "education", "effect", "end", "error", "event", "example", "exchange", "existence", "expansion", "experience", "expert", "fact", "fall", "family", "father", "fear", "feeling", "fiction", "field", "fight", "fire", "flame", "flight", "flower", "fold", "food", "force", "form", "friend", "front", "fruit", "glass", "gold", "government", "grain", "grass", "grip", "group", "growth", "guide", "harbor", "harmony", "hate", "hearing", "heat", "help", "history", "hole", "hope", "hour", "humor", "ice", "idea", "impulse", "increase", "industry", "ink", "insect", "instrument", "insurance", "interest", "invention", "iron", "jelly", "join", "journey", "judge", "jump", "kick", "kiss", "knowledge", "land", "language", "laugh", "law", "lead", "learning", "leather", "letter", "level", "lift", "light", "limit", "linen", "liquid", "list", "look", "loss", "love", "machine", "man", "manager", "mark", "market", "mass", "meal", "measure", "meat", "meeting", "memory", "metal", "middle", "milk", "mind", "mine", "minute", "mist", "money", "month",
							"morning", "mother", "motion", "mountain", "move", "music", "name", "nation", "need", "news", "night", "noise", "note", "number", "observation", "offer", "oil", "operation", "opinion", "order", "organisation", "ornament", "owner", "page", "pain", "paint", "paper", "part", "paste", "payment", "peace", "person", "place", "plant", "play", "pleasure", "point", "poison", "polish", "porter", "position", "powder", "power", "price", "print", "process", "produce", "profit", "property", "prose", "protest", "pull", "punishment", "purpose", "push", "quality", "question", "rain", "range", "rate", "ray", "reaction", "reading", "reason", "record", "regret", "relation", "religion", "representative", "request", "respect", "rest", "reward", "rhythm", "rice", "river", "road", "roll", "room", "rub", "rule", "run", "salt", "sand", "scale", "science", "sea", "seat", "secretary", "selection", "self", "sense", "servant", "sex", "shade", "shake", "shame", "shock", "side", "sign", "silk", "silver", "sister", "size", "sky", "sleep", "slip", "slope", "smash", "smell", "smile", "smoke", "sneeze", "snow", "soap", "society", "son", "song", "sort", "sound", "soup", "space", "stage", "start", "statement", "steam", "steel", "step", "stitch", "stone", "stop", "story", "stretch", "structure", "substance", "sugar", "suggestion", "summer", "support", "surprise", "swim", "system", "talk", "taste", "tax", "teaching", "tendency", "test", "theory", "thing", "thought", "thunder", "time", "tin", "top", "touch", "trade", "transport", "trick", "trouble", "turn", "twist", "unit", "use", "value", "verse", "vessel", "view", "voice", "walk", "war", "wash", "waste", "water", "wave", "wax", "way", "weather", "week", "weight", "wind", "wine", "winter", "woman", "wood", "wool", "word", "work", "wound", "writing", "year"};

#define MENU_COUNT 4

#define WELCOME_BACKGROUND "images//welcome.bmp"
#define MENU_START_GAME "images//button//start_game.bmp"
#define MENU_START_GAME_EXPANDED "images//button//lstart_game.bmp"
#define MENU_LEVEL "images//button//level.bmp"
#define MENU_LEVEL_EXPANDED "images//button//llevel.bmp"
#define MENU_HELP "images//button//help.bmp"
#define MENU_HELP_EXPANDED "images//button//lhelp.bmp"
#define MENU_QUIT "images//button//quit.bmp"
#define MENU_QUIT_EXPANDED "images//button//lquit.bmp"
#define HELP_BACKGROUND "images//help.bmp"
#define LEVEL_SELECTION_BACKGROUND "images//level.bmp"
#define PLAYER_1_SELECTION_BACKGROUND "images//player1.bmp"
#define PLAYER_2_SELECTION_BACKGROUND "images//player2.bmp"
#define PLAYER_SELECTION_TICK_MARK "images//tick.bmp"
#define RESULT_BACKGROUND "images//you_win.bmp"
#define SCOREBOARD "images//scorboard.bmp"
#define CHARACTER_BOY "images//character//boy.bmp"
#define CHARACTER_GRU "images//character//gru.bmp"

#define FONT_FAMILY GLUT_BITMAP_TIMES_ROMAN_24

const char l3Letter[52][22] = {"images//level3//a.bmp", "images//level3//b.bmp", "images//level3//c.bmp", "images//level3//d.bmp", "images//level3//e.bmp", "images//level3//f.bmp", "images//level3//g.bmp", "images//level3//h.bmp", "images//level3//i.bmp", "images//level3//j.bmp", "images//level3//k.bmp", "images//level3//l.bmp", "images//level3//m.bmp", "images//level3//n.bmp", "images//level3//o.bmp", "images//level3//p.bmp", "images//level3//q.bmp", "images//level3//r.bmp", "images//level3//s.bmp", "images//level3//t.bmp", "images//level3//u.bmp", "images//level3//v.bmp", "images//level3//w.bmp", "images//level3//x.bmp", "images//level3//y.bmp", "images//level3//z.bmp"};
const char l2Letter[52][22] = {"images//level2//a.bmp", "images//level2//b.bmp", "images//level2//c.bmp", "images//level2//d.bmp", "images//level2//e.bmp", "images//level2//f.bmp", "images//level2//g.bmp", "images//level2//h.bmp", "images//level2//i.bmp", "images//level2//j.bmp", "images//level2//k.bmp", "images//level2//l.bmp", "images//level2//m.bmp", "images//level2//n.bmp", "images//level2//o.bmp", "images//level2//p.bmp", "images//level2//q.bmp", "images//level2//r.bmp", "images//level2//s.bmp", "images//level2//t.bmp", "images//level2//u.bmp", "images//level2//v.bmp", "images//level2//w.bmp", "images//level2//x.bmp", "images//level2//y.bmp", "images//level2//z.bmp"};
const char l1Letter[52][22] = {"images//level1//a.bmp", "images//level1//b.bmp", "images//level1//c.bmp", "images//level1//d.bmp", "images//level1//e.bmp", "images//level1//f.bmp", "images//level1//g.bmp", "images//level1//h.bmp", "images//level1//i.bmp", "images//level1//j.bmp", "images//level1//k.bmp", "images//level1//l.bmp", "images//level1//m.bmp", "images//level1//n.bmp", "images//level1//o.bmp", "images//level1//p.bmp", "images//level1//q.bmp", "images//level1//r.bmp", "images//level1//s.bmp", "images//level1//t.bmp", "images//level1//u.bmp", "images//level1//v.bmp", "images//level1//w.bmp", "images//level1//x.bmp", "images//level1//y.bmp", "images//level1//z.bmp"};
const char digit[50][22] = {"images//digit//0.bmp", "images//digit//1.bmp", "images//digit//2.bmp", "images//digit//3.bmp", "images//digit//4.bmp", "images//digit//5.bmp", "images//digit//6.bmp", "images//digit//7.bmp", "images//digit//8.bmp", "images//digit//9.bmp"};

#endif
