import java.lang.*;
import java.io.*;

class sort{

    public void sortColors(int[] nums) {
        
        int counter = 0;
        int j = 0;
        
        for(int i = 1; i < nums.length; i++){
            
            if(nums[i-1] < nums[i]){
                
                // System.out.println("%d < %d", nums[i-1], nums[i]);
                // keep same position
                
            }else{
                // next is larger
                int holder = nums[i-1];
                int hol = nums[i];
                nums[i-1] = hol;
                nums[i] = holder;
            }
            
        
        }
        
    }


    public static void main(String[] args) {

    }

    
}

