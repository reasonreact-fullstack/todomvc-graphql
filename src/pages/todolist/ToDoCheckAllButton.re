let styles = [%raw {| require("./ToDoCheckAllButton.scss") |}]
let component = ReasonReact.statelessComponent("ToDoCheckAllButton")

let make = (_children) => {
    ...component,

    render: _self => {
        <button className=styles##button>
            <span className=styles##buttonText>{ ReasonReact.string({j|❯|j}) }</span>
        </button>
    }
}
