//
// Created by Igli milaqi on 04/05/2020.
//

#ifndef CROW_DAMAGEDEALER_H
#define CROW_DAMAGEDEALER_H


struct DamageDealer
{
    enum Type
    {
        Sword,
        Pike,
        Arrow,
        NONE
    };

    float damageRate = 0.5f;

    Type damageDealerType = NONE;
    Type strongAgainst = NONE;

};


#endif //CROW_DAMAGEDEALER_H
