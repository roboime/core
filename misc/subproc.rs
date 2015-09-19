use std::process::{Stdio, Command, Child};
use std::io::{BufRead, BufReader, Write};

fn main() {
    let mut child = Command::new("./subproc_demo_echo.sh")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn().ok().expect("could not create subprocess");

    if let Child { stdin: Some(ref mut child_in), stdout: Some(ref mut child_out), stderr: Some(ref mut child_err), .. } = child {
        let mut lines = BufReader::new(child_out).lines();

        writeln!(child_in, "foo").unwrap();
        println!("got: {:?}", lines.next());

        writeln!(child_in, "bar").unwrap();
        println!("got: {:?}", lines.next());

        writeln!(child_in, "enough").unwrap();
        println!("got: {:?}", lines.next());

        // let's just confirm there's nothing else
        println!("got: {:?}", lines.next());

        for line in BufReader::new(child_err).lines() {
            println!("got: {:?}", line);
        }

    } else {
        println!("child stdin or stdout not bound");
    }

    println!("{:?}", child.wait());
}
