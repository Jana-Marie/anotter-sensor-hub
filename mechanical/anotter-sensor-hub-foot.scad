$fn = 100;

if($preview){
    pcb();
    translate([1*44.3/2,1*35.3/2,1.6])rotate([0,0,180])stand();
    translate([1*44.3/2,-1*35.3/2,1.6])rotate([0,0,90])stand();
    translate([-1*44.3/2,1*35.3/2,1.6])rotate([0,0,270])stand();
    translate([-1*44.3/2,-1*35.3/2,1.6])rotate([0,0,0])stand();
    translate([0,0,1.6+15])sensor();
} else {
    stand();
}

module stand(h=15,h2=5){
    color("pink")
    difference(){
        union(){
            // outer hull
            hull(){
                // inner structure
                union(){
                    translate([0,2,h/2])cube([8,4,h],center=true);
                    translate([2,0,h/2])cube([4,8,h],center=true);
                    cylinder(r=4,h=h);
                }
                // lower hull
                union(){
                    translate([0,2,-h2/2])cube([12,4,h2],center=true);
                    translate([2,0,-h2/2])cube([4,12,h2],center=true);
                    translate([0,0,-h2])cylinder(r=6,h=h2);
                }
                // upper hull
                union(){
                    translate([0,1,h+h2/2])cube([12,6,h2],center=true);
                    translate([1,0,h+h2/2])cube([6,12,h2],center=true);
                    translate([-2,-2,h])cylinder(r=4,h=h2);
                }
            }
        } union(){
            // screwholes
            translate([0,0,-0.01])cylinder(d=2.8,h=h/3*2);
            // upper cutout
            translate([0,0,h+h/4])cube([8.1,8.1,h/2],center=true);
            // PCB cutout
            union(){
                translate([0,2,-h/2])cube([8,4,h],center=true);
                translate([2,0,-h/2])cube([4,8,h],center=true);
                translate([0,6,0])cube([12,4,h*3],center=true);
                translate([6,0,0])cube([4,12,h*3],center=true);
                translate([0,0,-h])cylinder(r=4,h=h);
            }
        }
    }
}

module pcb(thickness=1.6){
    difference(){
        union(){
            // PCB
            color("green")
            minkowski(){
                r=4;
                translate([0,0,thickness/2-0.1/2])cube([52.3-r-r,43.4-r-r, thickness-0.1],center=true);
                cylinder(r=r,h=0.1);
            }
            // Screwholeplates
            color("gold")
            for(i = [-1:2:1]){
                for(j = [-1:2:1]){
                    translate([i*44.3/2,j*35.3/2,0])cylinder(d=6.4,h=thickness+0.01);
                }
            }
            // ESP32
            translate([-1,10,thickness])
            union(){
                color("black")translate([0,0,0.6/2])cube([25,18,0.6],center=true);
                color("silver")translate([-2.75,0,0.6+1.2/2])cube([18,16.5,1.2],center=true);
            }
            // USB
            color("silver")translate([-22,8,3.2/2+thickness])cube([9,7.4,3.2],center=true);
        } union(){
            // Screwholes
            for(i = [-1:2:1]){
                for(j = [-1:2:1]){
                    translate([i*44.3/2,j*35.3/2,-thickness/2])cylinder(d=3.2,h=thickness*2);
                }
            }
        }
    }
}

module sensor(){
    difference(){
        union(){
            // main body
            color("DarkSlateGray")translate([0,0,13.2/2])cube([52.3,43.3,13.2],center=true);
            // fan
            color("DarkSlateGray")translate([52.2/2-27.24/2,-43.2/2+15/2,22.3/2])cube([27.24,15,22.3],center=true);
            // intake
            color("DarkSlateGray")translate([-52.2/2+27.24/2,-43.2/2+10/2,16.7/2])cube([13.69,10,16.7],center=true);
        } union(){
        }
    }
}