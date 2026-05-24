"use client";

import { Game } from "@/lib/api";
import { motion } from "motion/react";
import { GenresList } from "./genres-list";
import { Rating } from "./rating";
import { cn } from "@/lib/utils";

type Props = {
    game: Game,
    expanded: boolean,
}

export function GameContent({ game, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">
            
            <div>
                <h2 className={cn("font-bold truncate", expanded ? "text-5xl" : "text-base")}>
                    {game.title}
                </h2>

                <Rating rating={game.rating} />
            </div>

            <p className={cn("text-sm text-muted-foreground", expanded ? "text-lg" : "text-sm")}>
                {game.developer}
            </p>
            
            <GenresList genres={game.genres} mediaId={game.id} />

            {expanded && (

                <motion.div
                    initial={{
                        opacity: 0,
                        y: 10,
                    }}

                    animate={{
                        opacity: 1,
                        y: 0,
                    }}

                    transition={{
                        delay: 0.2,
                    }}
                >

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.description}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.platform}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.multiplayer ? "Multiplayer" : "Single player"}
                    </p>
                </motion.div>
            )}

        </div>
    );
}