#define motorXAxis_pos 1
#define motorXAxis_neg 2
#define motorYAxis_pos 3
#define motorYAxis_neg 4

/*
    Motor x-axis:
        positive: rotate rotate
        negative: rotate left 
    Motor y-axis:
        positive: rotate up 
        negative: rotate down
*/

void setup() {
    pinMode(motorXAxis_pos,OUTPUT);
    pinMode(motorXAxis_neg,OUTPUT);
    pinMode(motorYAxis_pos,OUTPUT);
    pinMode(motorYAxis_neg,OUTPUT);
}

void loop() {
    /*  
    TODO:
        Get x, y
        Start rotating
        Delay based on calculations
        Stop rotating
    */
} 

void rotateLeft() {
    digitalWrite(motorXAxis_pos, LOW);
    digitalWrite(motorXAxis_neg, HIGH);
}

void rotateRight() {
    digitalWrite(motorXAxis_pos, HIGH);
    digitalWrite(motorXAxis_neg, LOW);
}

void rotateUp() {
    digitalWrite(motorYAxis_pos, HIGH);
    digitalWrite(motorYAxis_neg, LOW);
}

void rotateDown() {
    digitalWrite(motorYAxis_pos, LOW);
    digitalWrite(motorYAxis_neg, HIGH);
}

void stopAll() {
    stopHorizontal();
    stopVertical();
}

void stopHorizontal() {
    digitalWrite(motorXAxis_neg, LOW);
    digitalWrite(motorXAxis_neg, LOW);
}

void stopVertical() {
    digitalWrite(motorYAxis_pos, LOW);
    digitalWrite(motorYAxis_neg, LOW);
}