#ifndef DEF_TEST
#define DEF_TEST

#include <string>

class Duree
{
	protected:
		//Attributs
		int m_heures;
		int m_minutes;
		int m_secondes;
	
	public:
		//Constructeurs
		Duree(int heures=0, int minutes=0, int secondes=0)
		:	m_heures(heures),
			m_minutes(minutes),
			m_secondes(secondes)
		{
			if(m_minutes>=60)
			{
				int nb_heures=0, nb_minutes=0;
				
				nb_heures=m_minutes/60;
				
				m_heures += nb_heures;
				
				nb_minutes=m_minutes%60;
				
				m_minutes=nb_minutes;
			}
			
			if(m_secondes>=60)
			{
				int nb_min=0, nb_secondes=0;
				
				nb_min=m_secondes/60;
				
				m_minutes += nb_min;
				
				if(m_minutes>=60)
				{
					int nb_heures=0, nb_minutes=0;
					
					nb_heures=m_minutes/60;
					
					m_heures += nb_heures;
					
					nb_minutes=m_minutes%60;
					
					m_minutes=nb_minutes;
				}
				
				nb_secondes=m_secondes%60;
				
				m_secondes=nb_secondes;	
			}
		}
		
		//Fonctions membres	
		
		void showTime()
		{
			std::cout << "Heures: " << m_heures << " ; " << "Minutes: " << m_minutes << " ; " << "Secondes: " << m_secondes << std::endl; 
		}
		
		bool isEqual(const Duree& b) const
		{
			return (m_heures == b.m_heures and m_minutes == b.m_minutes and m_secondes == b.m_secondes);
		}
		
		bool isUpper(const Duree& b) const
		{
			if(m_heures>b.m_heures)
			{
				return true;
			}
			else if(m_heures==b.m_heures)
			{
				if(m_minutes>b.m_minutes)
				{
					return true;
				}
				else if(m_minutes==b.m_minutes)
				{
					if(m_secondes>b.m_secondes)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
};

bool operator==(const Duree& a, const Duree& b);

bool operator>(const Duree& a, const Duree& b);

#endif /*TEST*/

