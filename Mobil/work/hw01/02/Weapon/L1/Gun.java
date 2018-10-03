package Weapon.L1;
import Weapon.Ranged;

public interface Gun extends Ranged 
{
    public Integer shoot()
    {
        return new Integer(9);
    }    
}