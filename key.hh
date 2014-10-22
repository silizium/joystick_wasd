#ifndef __KEY_HH__
#define __KEY_HH__

class Key{
	__u16 upkey, dnkey;
public:
	Key(__u16 upkey, __u16 dnkey);
	~Key();
	int tick();
};

#endif