const API = "http://127.0.0.1:18080";

function upload() {
    const title = document.getElementById("title").value;
    const teacher = document.getElementById("teacher").value;
    const file = document.getElementById("file").files[0];

    if (!file) {
        alert("اختار فيديو");
        return;
    }

    const form = new FormData();
    form.append("title", title);
    form.append("teacher", teacher);
    form.append("file", file);

    fetch(API + "/upload", {
        method: "POST",
        body: form
    })
        .then(res => res.text())
        .then(() => {
            alert("Upload Success ✅");
            loadVideos();
        })
        .catch(() => alert("Backend مش شغال ❌"));
}
