function add_note(){
var new_note = document.createElement("div");
var text = document.createElement("p");
var parent = document.getElementById("notepad");
var input = document.getElementById("my_note").value;
new_note.appendChild(text).innerHTML = input;
new_note.className = "note";
parent.appendChild(new_note);
}	