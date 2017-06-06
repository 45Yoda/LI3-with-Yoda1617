package engine;

import li3.Interface;

import java.util.ArrayList;
import java.io.FileNotFoundException;

public class QueryEngineImpl implements Interface {

    private Registo reg;

    public void init() {
        this.reg = new Registo();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
        CatArtigos cArt = reg.getCatArt();
        CatContrib cCont = reg.getCatCont();
        try{
            Parser.parseDoc(nsnaps, snaps_paths, cArt, cCont);
        }
        catch(FileNotFoundException e){
            System.err.println("FileNotFoundException: " + e.getMessage());
        }

    }

    public long all_articles() {
    }

    public long unique_articles() {

        return 0;
    }

    public long all_revisions() {

        return 0;
    }

    public ArrayList<Long> top_10_contributors() {

        return new ArrayList<Long>();
    }

    public String contributor_name(long contributor_id) {

        return " ";
    }

    public ArrayList<Long> top_20_largest_articles() {

        return new ArrayList<Long>();
    }

    public String article_title(long article_id) {

        return " ";
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return new ArrayList<Long>();
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return new ArrayList<String>();
    }

    public String article_timestamp(long article_id, long revision_id) {

        return " ";
    }

    public void clean() {

    }
}
