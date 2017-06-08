package engine;

import java.util.Comparator;
import java.io.Serializable;

public class ComparatorWords implements Comparator<Artigo>, Serializable {

    public int compare(Artigo a1, Artigo a2){
            long words1 = a1.getWords();
            long words2 = a2.getWords();

            if(words1 <= words2) return 1;
            if(words1 > words2) return -1;
            else return 0;
   }
}