/* 
두 행렬의 크기를 입력받아서 필요한 만큼의 메모리를 동적으로 할당하여 행렬
의 내용을 저장하고 두 행렬을 더하는 프로그램을 작성하시오.

를 러스트의 Vec<T>를 사용하여 구현하시오

*/
use std::io;
use rand::Rng;

fn create_Matrix(rows: i32, cols:i32)->Vec<Vec<i32>>{
    let mut rng = rand::thread_rng();
    let mut matrix: Vec<Vec<i32>> = Vec::new();

    for _ in 0..rows{
        let mut row: Vec<i32> =Vec::new();
        for _ in 0..cols{
            let random_number = rng.gen_range(1..=3);
            row.push(random_number);
        }
        matrix.push(row)
    }
    matrix
}

fn print_Matrix(matrix: &Vec<Vec<i32>>) {
    for row in matrix{
        for &element in row{
            print!("{} ",element);
        }
        println!();
    }
}

fn sum_Matrix(mat1: &Vec<Vec<i32>>, mat2: &Vec<Vec<i32>>) ->Vec<Vec<i32>>{
    let mut result: Vec<Vec<i32>> = vec![vec![0; mat1[0].len()]; mat1.len()];
    for i in 0..mat1.len() {
        for j in 0..mat1[0].len(){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    result
}

pub fn p9() {
    let mut input1 = String::new();
    let mut input2 = String::new();
    
    io::stdin().read_line(&mut input1)
        .expect("입력을 받을 수 없습니다.");
    io::stdin().read_line(&mut input2)
        .expect("입력을 받을 수 없습니다.");
    
    let rows : i32 = input1.trim().parse()
        .expect("input1 정수변환 불가능");
    let cols : i32 = input2.trim().parse()
        .expect("input2 정수변환 불가능");

    let mut rng = rand::thread_rng();

    println!("rows: {}, cols: {}",rows,cols);

   
    let mat1 = create_Matrix(rows,cols);
    let mat2 = create_Matrix(rows,cols);
    println!("matrix1:");
    print_Matrix(&mat1);
    println!("matrix2:");
    print_Matrix(&mat2);

    println!("mat1 + mat2 :");
    sum_Matrix(&mat1,&mat2);

    let mat3 = sum_Matrix(&mat1,&mat2);
    print_Matrix(&mat3);

}

