#pragma once
#include "CActor.h"
#include <iostream>

class Homer : public CActorCard
{
public:
	explicit Homer(Money cash, CBank& bank)
		: CActorCard(cash, bank) {}
	
	void Act(Actors& actors) override;
};

class Marge : public CActorCard
{
public:
    explicit Marge(Money cash, CBank& bank)
        : CActorCard(cash, bank) {}

    void Act(Actors& actors) override;
};

class Apu : public CActorCard
{
public:
    explicit Apu(Money cash, CBank& bank)
        : CActorCard(cash, bank) {}

    void Act(Actors& actors) override;
};

class MrBurns : public CActorCard
{
public:
    explicit MrBurns(Money cash, CBank& bank)
        : CActorCard(cash, bank) {}

    void Act(Actors& actors) override;
};

class Snake : public CActorCard
{
public:
    explicit Snake(Money cash, CBank& bank)
        : CActorCard(cash, bank) {}

    void Act(Actors& actors) override;
};

class Smithers : public CActorCard
{
public:
    explicit Smithers(Money cash, CBank& bank)
        : CActorCard(cash, bank) {}

    void Act(Actors& actors) override;

private:
    int m_paranoia = 0;
    const int m_paranoia_border = 3;
};

class Bart : public CActor
{
public:
    explicit Bart(Money cash)
        : CActor(cash) {}

    void Act(Actors& actors) override;
};

class Lisa : public CActor
{
public:
    explicit Lisa(Money cash)
        : CActor(cash) {}

    void Act(Actors& actors) override;
};

class Nelson : public CActor
{
public:
    explicit Nelson(Money cash)
        : CActor(cash) {}

    void Act(Actors& actors) override;
};