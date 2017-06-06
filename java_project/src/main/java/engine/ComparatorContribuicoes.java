import java.util.Comparator;
import java.io.Serializable;


//Compara as Contribuições de dois Contribuidores
public class ComparatorContribuicoes implements Comparator<Contribuidor>, Serializable {

    public int compare(Contribuidor c1, Contribuidor c2){
            int cont1 = c1.getCont();
            int cont2 = c2.getCont();
            long id1 = c1.getId();
            long id2 = c2.getId();

            if(cont1 < cont2) return 1;
            if(cont1 > cont2) return -1;
            else
                //è assim? REVIEW
                if(id1 < id2) return -1
                if(id1 > id2) return 1;
                else return 0;

    }
}
