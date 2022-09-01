package application.law27076.sudoku;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.content.Context;
import android.graphics.Color;

public class MainActivity extends AppCompatActivity {

    private class Cell{
        int value;
        boolean fixed;
        Button bt;
        public Cell(int initvalue, Context THIS){
            value = initvalue;
            if(value!=0) fixed = true;
            else fixed = false;
            bt = new Button(THIS);
            if(fixed) bt.setText(String.valueOf(value));
            else bt.setTextColor(Color.BLUE);
            bt.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View view){
                    if(fixed) return;
                    value++;
                    if(value>9) value = 1;
                    bt.setText(String.valueOf(value));
                }
            });
        }
    }
    boolean completed(){
        for(int i = 0;i<9;i++)
            for(int j = 0;j<9;j++)
                if(table[i][j].value == 0)
                    return false;
                return true;
    }
    boolean correct(int i1, int j1, int i2, int j2){
        boolean[] seen = new boolean[10];
        for(int i = 1;i<=9;i++) seen[i] = false;
        for(int i = i1;i<i2;i++) {
            for (int j = j1; j < j2; j++) {
                int value = table[i][j].value;
                if(value != 0){
                    if(seen[value]) return false;
                    seen[value] = true;
                }
            }
        }
        return true;
    }
    boolean correct(){
        for(int i = 0;i<9;i++){
            if(!correct(i,0,i,9)) return false;
        }
        for(int j = 0;j<9;j++)
            if(!correct(0,j,9,j)) return false;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(!correct(3*i,3*j,3*i+3,3*j+3)) return false;
        return true;
    }
    Cell[][] table;
    String input =  "2 9 ? 7 4 3 8 6 1 "+
                    "4 ? 1 8 6 5 9 ? 7 "+
                    "8 7 6 1 9 2 5 4 3 "+
                    "3 8 7 4 5 9 2 1 6 "+
                    "6 1 2 3 ? 7 4 ? 5 "+
                    "? 4 9 2 ? 6 7 3 8 "+
                    "? ? 3 5 2 4 1 8 9 "+
                    "9 2 8 6 7 1 ? 5 4 "+
                    "1 5 4 9 3 ? 6 7 2 ";
    String[] split = input.split(" ");
    TableLayout tl;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
        table = new Cell[9][9];
        tl = new TableLayout(this);
        for(int i = 0;i<9;i++){
            TableRow tr = new TableRow(this);
            for(int j = 0;j<9;j++){
                String s = split[i*9+j];
                Character c = s.charAt(0);
                table[i][j] = new Cell(c == '?'?0:c-'0',this);
                tr.addView(table[i][j].bt);
            }
            tl.addView(tr);
        }
        tl.setShrinkAllColumns(true);
        tl.setStretchAllColumns(true);

        setContentView(tl);
    }
}