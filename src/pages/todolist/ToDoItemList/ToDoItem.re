let styles = [%raw {| require("./ToDoItem.scss") |}]
let component = ReasonReact.statelessComponent("ToDoItem")

let make = (~todo: ToDoTypes.todo, _children) => {
    ...component,

    render: _self => {
        let style = style => {
            Cn.make([
                style,
                styles##completed->Cn.ifTrue(todo.completed)
            ])
        };

        <li className=styles##wrap>
            <button className=style(styles##checkbox)></button>
            <span className=style(styles##text)>{ ReasonReact.string(todo.content) }</span>
            <button className=styles##removeButton>{ ReasonReact.string({j|×|j}) }</button>
        </li>
    }
}
