let styles: ToDoInputStyles.definition = [%raw {| require("./ToDoInput.scss") |}]
let component = ReasonReact.statelessComponent("ToDoInput")

let make = (~newTodo=false, ~placeholder="", _children) => {
    ...component,

    render: _self => {
        <input type_="text" 
            className=Cn.make([
                styles##textbox,
                styles##newTodo->Cn.ifTrue(newTodo),
            ])
            placeholder
        />
    }
}
