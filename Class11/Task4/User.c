#include "User.h"
#include <stdlib.h>

void InitUser(User* user, HashMap* map, int db_tag)
{
	errno_t s = 0;
	user->name = map->get(map, "name", &s);
	user->surname = map->get(map, "surname", &s);
	user->credentials = map->get(map, "credentials", &s);
	user->shadow_balance = atoll(map->get(map, "balance", &s));
	user->cash = atoll(map->get(map, "cash", &s));
	user->phone_balance = atoi(map->get(map, "phone_b", &s));
	user->shadow_pass = map->get(map, "psw_hash", &s);
	user->db_tag = db_tag;
	if (s != ERR_NO) panic("User :: invalid userdata");
}

void ExtractUserData(HashMap* out, User* user)
{
	const char balance_str[20];
	const char cash_str[20];
	const char phone_str[20];
	_i64toa_s(user->shadow_balance, balance_str, 20, 10);
	_i64toa_s(user->cash, cash_str, 20, 10);
	_i64toa_s(user->phone_balance, phone_str, 20, 10);
	if (out->__notnull__ == 0) panic("User :: null <HashMap>");
	if(out->size != 0) panic("User :: try to write to not empty map");
	out->put(out, "name", user->name);
	out->put(out, "surname", user->surname);
	out->put(out, "credentials", user->credentials);
	out->put(out, "balance", balance_str);
	out->put(out, "cash", cash_str);
	out->put(out, "phone_b", phone_str);
	out->put(out, "psw_hash", user->shadow_pass);
}

void UnboxUserData(DataBox* out, User* user)
{
	const char balance_str[20];
	const char cash_str[20];
	const char phone_str[20];
	_i64toa_s(user->shadow_balance, balance_str, 20, 10);
	_i64toa_s(user->cash, cash_str, 20, 10);
	_i64toa_s(user->phone_balance, phone_str, 20, 10);
	out->kv.clear(&out->kv);
	out->vv.clear(&out->vv);
	out->kv.put(&out->kv, "name");
	out->kv.put(&out->vv, user->name);
	out->kv.put(&out->kv, "surname");
	out->kv.put(&out->vv, user->surname);
	out->kv.put(&out->kv, "credentials");
	out->kv.put(&out->vv, user->credentials);
	out->kv.put(&out->kv, "balance");
	out->kv.put(&out->vv, balance_str);
	out->kv.put(&out->kv, "cash");
	out->kv.put(&out->vv, cash_str);
	out->kv.put(&out->kv, "phone_balance");
	out->kv.put(&out->vv, phone_str);
	out->kv.put(&out->kv, "psw_hash");
	out->kv.put(&out->vv, user->shadow_pass);
}
