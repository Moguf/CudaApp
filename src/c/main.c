#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP_SIZE 10000
#define MOL_SIZE 20
#define MOL_XYZ MOL_SIZE*3
#define MASS 1 

int show(float *xyz);
int init(float *xyz,float *vel);
int calStep(float *xyz,float *vel);
float force(float *xyz,float *accel);
float distance(float x1,float y1,float z1,float x2,float y2,float z2);

int main(void){
    float *xyz,*vel;
    xyz=(float *)malloc(sizeof(float)*MOL_XYZ);
    vel=(float *)malloc(sizeof(float)*MOL_XYZ);
    
    init(xyz,vel);
    show(xyz);
    calStep(xyz,vel);
    
    free(xyz);
    free(vel);
    return 0;
}

int init(float *xyz,float *vel){
    int i_xyz;
    srand(10);
    for(i_xyz=0;i_xyz<MOL_XYZ;i_xyz++){
        xyz[i_xyz]=(rand()%1000)*0.01;
        vel[i_xyz]=(rand()%10)*0.1;
    }
    return 0;
}

int show(float *xyz){
    int i_xyz;
    for(i_xyz=0;i_xyz<MOL_XYZ;i_xyz++){
        if((i_xyz)%3==0)
            printf("ATOM   %4d  C   ARA A   1    ",i_xyz/3+1);
        printf("%8.3f",xyz[i_xyz]);
        if((i_xyz+1)%3==0)
            puts("  1.00  1.00           N  ");
    }
    puts("ENDMDL");
    return 0;
}    

int calStep(float *xyz,float *vel){
    float *accel;
    float h=0.5;
    int i_step,i_mol,i_xyz;
    float *xyz_n,*xyz_nn;

    xyz_n=(float *)malloc(sizeof(float)*MOL_XYZ);        
    xyz_nn=(float *)malloc(sizeof(float)*MOL_XYZ);        
    accel=(float *)malloc(sizeof(float)*MOL_XYZ);    

    //first step
    force(xyz,accel);
    for(i_xyz=0;i_xyz<MOL_XYZ;i_xyz++){
        xyz_n[i_xyz]=xyz[i_xyz]+h*vel[i_xyz]+h*h/2*accel[i_xyz];
    }
    for(i_step=1;i_step<STEP_SIZE-2;i_step++){
        force(xyz_n,accel);
        for(i_xyz=0;i_xyz<MOL_XYZ;i_xyz++){
            xyz_nn[i_xyz]=2*xyz_n[i_xyz]-xyz[i_xyz]+h*h*accel[i_xyz];
        }
        show(xyz_n);
        xyz=xyz_n;
        xyz_n=xyz_nn;
    }
    show(xyz_n);
    free(xyz_n);
    return 0;
}

float force(float *xyz,float *accel){
    int i_xyz,i_mol,j_mol;
    float dist;
    float ix,iy,iz,jx,jy,jz;

    for(i_xyz=0;i_xyz<MOL_XYZ;i_xyz++)
        accel[i_xyz]=0;

    for(i_mol=0;i_mol<MOL_SIZE;i_mol++){
        for(j_mol=0;j_mol<MOL_SIZE;j_mol++){
            ix,iy,iz,jx,jy,jz=xyz[i_mol],xyz[i_mol+1],xyz[i_mol+2],xyz[j_mol],xyz[j_mol+1],xyz[j_mol+2];
            dist=distance(ix,iy,iz,jx,jy,jz);
            accel[i_mol]+=(1/(pow(dist,13))-1/(pow(dist,7)))*(ix-jx);
            accel[i_mol]+=(1/(pow(dist,13))-1/(pow(dist,7)))*(iy-jy);
            accel[i_mol]+=(1/(pow(dist,13))-1/(pow(dist,7)))*(iz-jz);
        }
    }

    return 0;
}
float distance(float x1,float y1,float z1,float x2,float y2,float z2){
    return sqrt(pow((x1-x2),2)+pow((y1-y2),2)+pow((z1-z2),2));
}
