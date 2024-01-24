use std::vec;

use serial2::SerialPort;


fn main() {
    let res = read(15).unwrap();
    print!("{:?}", res);
    print!("{:?}", inputs(res));
}



fn read(length: usize, ) -> Result<String, Box<dyn std::error::Error>> {
    let port = SerialPort::open("/dev/ttyUSB0", 9600)?;
    let mut buffer = vec![0; length];
    let mut total_read = 0;

    while total_read < buffer.len() {
        match port.read(&mut buffer[total_read..]) {
            Ok(read) => total_read += read,
            Err(ref e) if e.kind() == std::io::ErrorKind::TimedOut => (),
            Err(e) => return Err(e.into()),
        }
    }

    port.write(&buffer[..total_read])?;

    let text = String::from_utf8_lossy(&buffer[..total_read]).into_owned();
    Ok(text)
}

fn inputs(text: String) -> Vec<f64>{
    let mut speed = text.split(";");
    let v: f64 = speed.next().unwrap().parse().unwrap();
    let mut x1: f64 = speed.next().unwrap().parse().unwrap();
    let mut x2: f64 = speed.next().unwrap().parse().unwrap();
    let mut x3: f64 = speed.next().unwrap().parse().unwrap();
    let mut m1 = v;
    let mut m2 = v;
    let mut m3 = v;
    let mut m4 = v;
    let maxv: f64 = vec![x1,x2,x3].iter().max_by(|a, b| a.total_cmp(b)).unwrap().to_owned();
    if maxv.to_owned() > (1.0/3.0) {
        x1 = x1 * (1.0/3.0) / maxv;
        x2 = x2 * (1.0/3.0) / maxv;
        x3 = x3 * (1.0/3.0) / maxv;
    }
    m1 = v*(1.0+x1+x2-x3);
    m2 = v*(1.0-x1-x2-x3);
    m3 = v*(1.0-x1+x2+x3);
    m4 = v*(1.0+x1-x2+x3);
    return vec![m1,m2,m3,m4];
}